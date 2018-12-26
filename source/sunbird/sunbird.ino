#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "FS.h"
#include <ArduinoJson.h>
#include <Wire.h>
#include "config.h"
#include "display.h"
#include "debug.h"
Debugger debug(Serial, udp);

#include "adc.h"
#include "console.h"
#include "flash.h"
#include "i2c.h"
#include "led.h"
#include "motor.h"
#include "pages.h"
#include "wifi.h"
#include "timers.h" 

void setupSerial(){
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  Serial.printf("Starting DongOS...\n");
}

void setup(void) {
  setupSerial();
  setupI2C();
  setupLCD();
  //////console.println("Start DongOS..");
  checkFlash();
  setupPWM();
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
  
  int remainingTimeBudget = ui.update();

  if (remainingTimeBudget > 0) {
    // You can do some work here
    // Don't do stuff if you are below your
    // time budget.
    delay(remainingTimeBudget);
  }
  
}

