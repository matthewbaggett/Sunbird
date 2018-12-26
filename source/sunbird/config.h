const char *ssid = "Plugnet";
const char *password = "UntilPrinciplePlasticEgg";

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

#define MULTICAST_PORT 12345
#define WEBSERVER_PORT 80
