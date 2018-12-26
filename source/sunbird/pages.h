#include <ESP8266WebServer.h>

ESP8266WebServer server(WEBSERVER_PORT);

void handleLogin() {
  SPIFFS.begin();
  ledColour(0,0,255);

  File f = SPIFFS.open("/login.html", "r");
  if (!f) {
    Serial.println("file open faiLED_BLUE");
  }
  char temp[f.size()];
  f.readBytes(temp, f.size());
  server.send(200, "text/html", temp);
  f.close();

  ledColour(0,0,0);
}

void handleLogout() {
  
}

bool checkAuth(){
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookies: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    return true;
  }else{
    Serial.println("Did not find cookies");
    server.sendHeader("Location", "/login");
    server.send(301);
    return false;
  }
}

void handleDashboard() {
  ledColour(0,0,255);
  if(checkAuth()){
    SPIFFS.begin();
    File f = SPIFFS.open("/dash.html", "r");
    if (!f) {
      Serial.println("file open for dash.html failed");
    }
    char temp[f.size()];
    f.readBytes(temp, f.size());
    server.send(200, "text/html", temp);
    f.close();
  }
  ledColour(0,0,0);
}

void handleLoginAction() {
  
  Serial.printf("Login attempt as: %s / %s", server.arg("username").c_str(), server.arg("password").c_str());
  ////console.printf("Login attempt as: %s / %s", server.arg("username").c_str(), server.arg("password").c_str());

  StaticJsonBuffer<400> jsonBuffer;
  SPIFFS.begin();
  File authFile = SPIFFS.open("/auth.json", "r");
  if (!authFile) {
    Serial.println("[FAIL Cannot open auth.json]");
    server.sendHeader("Location", "/login?error=Cannot open auth.json");
    server.send(301);
  }
  
  char temp[authFile.size()];
  authFile.readBytes(temp, authFile.size());
  Serial.println("Auth file:");
  Serial.println(temp);
  
  JsonArray& validUsers = jsonBuffer.parseArray(temp);

  // Test if parsing succeeds.
  if (!validUsers.success()) {
    Serial.println("[FAIL Auth parseObject() failed]");
    server.sendHeader("Location", "/login?error=Auth parseObject() failed");
    server.send(301);
    return;
  }

  bool loginSuccess = false;
  for (auto& validUser : validUsers){
    Serial.print("Is it \"");
    String userName = validUser["username"];
    String passWord = validUser["password"];
    Serial.print(userName);
    Serial.print("\"?");
    if(userName == server.arg("username") && passWord == server.arg("password")){
      Serial.println (" Yes");
      loginSuccess = true;
    }else{
      Serial.println (" No");
    }
  }

  authFile.close();
  if(loginSuccess){
    Serial.println("Login success, set cookie");
    ////console.println(" [SUCCESS]");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=1; Path=/; Max-Age=86400");
    server.sendHeader("Location", "/dashboard");
    server.send(301);
  }else{
    //console.println(" [BAD AUTH]");
    server.sendHeader("Location", "/login?error=Login Invalid");
    server.send(301);
  }
}


bool is_authentified() {
  Serial.println("Enter is_authentified");
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentification Successful");
      return true;
    }
  }
  Serial.println("Authentification Failed");
  return false;
}

void handleFavicon(){
  SPIFFS.begin();
  ledColour(0,0,255);
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  File f = SPIFFS.open("/img/favicon.ico", "r");
  if (!f) {
    Serial.println("file open faiLED_BLUE");
  }
  char temp[f.size()];
  f.readBytes(temp, f.size());
  server.send(200, "image/x-icon", temp);
  f.close();

  ledColour(0,0,0);
}

void handleReboot(){
  SPIFFS.begin();
  ledColour(255,0,0);

  Serial.println("Reboot ordered!");
  File f = SPIFFS.open("/reboot.html", "r");
  if (!f) {
    Serial.println("file open faiLED_BLUE");
  }
  char temp[f.size()];
  f.readBytes(temp, f.size());
  server.send(200, "text/html", temp);
  f.close();

  ledColour(0,0,0);
  ESP.restart();
}

void handleNotFound() {
  ledColour(0,0,255);
  Serial.print("404: ");
  Serial.print(server.uri());
  Serial.println(" does not exist.");
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  ledColour(0,0,0);
}


void drawGraph() {
  String out = "";
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10) {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send(200, "image/svg+xml", out);
}

void setupHttp(){
  //console.printf("Mount FS ");
  if(SPIFFS.begin()){
    //console.println("[OK]");
  }else{
    //console.println("[FAIL]");
  }
 
  server.serveStatic("/css", SPIFFS, "/css");
  server.serveStatic("/js", SPIFFS, "/js");
  server.serveStatic("/img", SPIFFS, "/img");
  server.on("/", handleLogin);
  server.on("/login", HTTP_GET, handleLogin);
  server.on("/logout", HTTP_GET, handleLogout);
  server.on("/dashboard", HTTP_GET, handleDashboard);
  server.on("/dologin", HTTP_POST, handleLoginAction);
  server.on("/test.svg", drawGraph);
  server.on("/favicon.ico", handleFavicon);
  server.on("/reboot", handleReboot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  
  //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize);

  //console.printf("Start HTTPd port %d ", WEBSERVER_PORT);
  server.begin();
  //console.println("[OK]");
  Serial.println("HTTP server started");
}


