#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "FS.h"
#include <ArduinoJson.h>

const char *ssid = "Plugnet";
const char *password = "UntilPrinciplePlasticEgg";

int pwmHz = 10;
int vcc;
int freeHeap;

#define STATE_OFF 0
#define STATE_SLEEP 1
#define STATE_ACTIVE 10

int state = STATE_OFF;

ESP8266WebServer server(80);

// Multicast declarations
IPAddress ipMulti(239, 0, 0, 57);
unsigned int portMulti = 12345;      // local port to listen on
WiFiUDP udp;

//ADC_MODE(ADC_VCC);

#include "debug.h"
Debugger debug(Serial, udp);

#include "adc.h"
#include "flash.h"
#include "led.h"
#include "motor.h"
#include "pages.h"
#include "wifi.h"
#include "timers.h"


void setup(void) {
  // Very first thing we gotta do is setup serial & pwm.
  Serial.begin(115200);
  analogWriteFreq(pwmHz);
  delay(100);
  Serial.println("");
  Serial.println("");
  Serial.println("");

  // Setup critical systems
  setupLed();
  setupADC();
  setupMotor();
  setupTimers();
  setupWifi();
  setupHttp();

  // LED off.
  ledColour(0,0,0);

  // An opportunity to test things after startup
  //testLed();
  //testFlash();
  //testMotor();
  motorOn(50);
  delay(100);
  motorOff();

  state = STATE_SLEEP;
}

void loop(void) {
  if (tickOccured == true){
    checkOneHz();
    tickOccured = false;
  }
  server.handleClient();
  yield();
}

