
ESP8266WebServer server(WEBSERVER_PORT);

// Multicast declarations
IPAddress ipMulti(239, 0, 0, 57);
unsigned int portMulti = MULTICAST_PORT;      // local port to listen on
WiFiUDP udp;

