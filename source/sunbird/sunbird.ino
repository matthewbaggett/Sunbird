#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "FS.h"
#include <ArduinoJson.h>
#include <Wire.h>
#include "config.h"
#include "connectivity.h"
#include "debug.h"
#include "adc.h"
#include "display.h"
#include "flash.h"
#include "i2c.h"
#include "led.h"
#include "motor.h"
#include "pages.h"
#include "wifi.h"
#include "timers.h" 

void setup(void) {
  // Very first thing we gotta do is setup serial, pwm & i2c.
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  Serial.println("Starting DongOS...");
  Serial.println("");
  
  // PWM service startup
  Serial.print("Starting PWM service at ");
  Serial.print(pwmHz);
  Serial.print("hz");
  analogWriteFreq(pwmHz);
  Serial.println(" ... [DONE]");

  // i2c service startup
  Serial.print("Starting i2c service on SDA=");
  Serial.print(I2C_SDA);
  Serial.print(" SCL=");
  Serial.print(I2C_SCL);
  //Wire.begin(I2C_SDA, I2C_SCL);
  Serial.println(" ... [DONE]");
  
  // Setup critical systems
  setupLed();
  setupADC();
  setupLCD();
  while(true){
    i2cScan();
    testLCD();
  }
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

