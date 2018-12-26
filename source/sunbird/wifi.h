String availableWifiNetworkStatement;

String scanWifiNetworks() {
  availableWifiNetworkStatement = "";
  byte numSsid = WiFi.scanNetworks();
  for (int thisNet = 0; thisNet < numSsid && thisNet < 10; thisNet++) {
    /*Serial.print("[Wifi][Scan] ");
      Serial.print(thisNet);
      Serial.print(") ");
      Serial.print(WiFi.SSID(thisNet));
      Serial.print("\tSignal: ");
      Serial.print(WiFi.RSSI(thisNet));
      Serial.println(" dBm");*/
    availableWifiNetworkStatement = availableWifiNetworkStatement + WiFi.BSSIDstr(thisNet).c_str() + "|" + WiFi.SSID(thisNet).c_str() + "|" + WiFi.RSSI(thisNet) + "dBm|Channel:" + WiFi.channel(thisNet) + "|" + (WiFi.encryptionType(thisNet) == ENC_TYPE_NONE ? "open" : "closed") + "\n";
    yield();
  }
  return availableWifiNetworkStatement;
}

void setupWifi_AP() {
  if (!softApEnabled) {
    return;
  }
  console.printf("Creating AP %s ", softApSSID);
  Serial.printf("Creating AP %s ", softApSSID);
  WiFi.softAPConfig(softApIp, softApGateway, softApSubnet);
  bool apSuccess = false;
  if(softApSecurityEnabled){
    apSuccess = WiFi.softAP(softApSSID, softApSecret);
  }else{
    apSuccess = WiFi.softAP(softApSSID);
  }
  if (apSuccess) {
    console.println("[OK]");
    Serial.println("[OK]");
  } else {
    console.println("[FAIL]");
    Serial.println("[FAIL]");
  }
  IPAddress apIP = WiFi.softAPIP();
  console.print("AP IP address: ");
  Serial.print("AP IP address: ");
  console.println(WiFi.softAPIP());
  Serial.println(WiFi.softAPIP());
}

void setupWifi_Client() {
  if (!clientEnabled) {
    return;
  }
  Serial.printf("Connecting to: %s\n", ssid);
  console.printf("Connecting %s ", ssid);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    ledColour(255, 0, 255);
    delay(250);
    ledColour(0, 0, 0);
    delay(250);
    Serial.print(".");
  }

  Serial.println("");
  Serial.printf("Connected to %s.\n", ssid);
  console.println("[OK]");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  console.print("IP: ");
  console.println(WiFi.localIP());
  for (int b = 0; b < 5; b++) {
    ledColour(0, 0, 0);
    delay(30);
    ledColour(0, 255, 0);
    delay(30);
  }
  ledColour(0, 0, 0);
}

void setupWifi_MDNS() {
  if (enableMDNS) {
    console.printf("Start MDNS ");
    if (MDNS.begin(mdnsName)) {
      console.println("[OK]");
      Serial.printf("MDNS responder started\n");
    } else {
      console.println("[FAIL]");
    }
  }
}

void setupWifi() {
  ledColour(255, 0, 0);
  //WiFi.mode(WIFI_AP_STA);
  WiFi.persistent(false);
  WiFi.disconnect();
  WiFi.setAutoConnect(false);
  WiFi.setAutoReconnect(true);
  WiFi.mode(WIFI_AP_STA);
  setupWifi_AP();
  setupWifi_Client();
  setupWifi_MDNS();
}
