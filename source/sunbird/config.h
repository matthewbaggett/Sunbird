const char *ssid = "Plugnet";
const char *password = "UntilPrinciplePlasticEgg";
const char *softApSSID="Buttplug";
const char *softApSecret="secret";

int pwmHz = 100;
int vcc;
int freeHeap;

#define STATE_OFF 0
#define STATE_SLEEP 1
#define STATE_ACTIVE 10
int state = STATE_OFF;

#define I2C_SDA 4
#define I2C_SCL 5
#define OLED_I2C_ADDRESS 0x3C
#define OLED_FONT 6 // Either 5 for 5x7 or 6 for 6x8

#define MULTICAST_PORT 12345
#define WEBSERVER_PORT 80
#define MDNS_NAME "Buttplug"
IPAddress ipMulti(239, 0, 0, 57);
unsigned int portMulti = MULTICAST_PORT;      // local port to listen on
WiFiUDP udp;
