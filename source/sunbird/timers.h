#define ONE_HZ_INTERVAL 1000000
#define SIXTY_HZ_INTERVAL 16666
#define SLEEP_BREATH_DIVISOR 10
#define SLEEP_BREATH_MAX_BRIGHTNESS_DIVISOR 0.5

extern "C" {
#include "user_interface.h"
}

unsigned long lastOneHz = 0;
unsigned long lastSixtyHz = 0;
unsigned long lastMotorHz = 0;
unsigned long oneHzCounter = 0;
unsigned long sixtyHzCounter = 0;
int wifiScanIntervalSeconds = 60;
int heartbeatIntervalSeconds = 1;
int heartbeatCount = 0;
bool tickOccured;

os_timer_t backgroundTaskTimer;

void heartBeat(){
  // Server-client remote control stuff here.
}

void sendDebugUDP(){
  float vcc = getVoltage();
  freeHeap = ESP.getFreeHeap();
  debug.printf(
    "Vcc: %f volts\nHeapFree: %d bytes\n", 
    vcc, 
    freeHeap
  );
}

void everyMinute() {
  sendDebugUDP();
}

void everyFiveMinutes() {
  
}

void oneHz(){
    
    if(oneHzCounter % heartbeatIntervalSeconds == 0 || oneHzCounter == 0){
      heartBeat();
    }
    
    if(oneHzCounter % 60 == 0 || oneHzCounter == 0){
      everyMinute();
    }
    
    if(oneHzCounter % 60 == 0 || oneHzCounter == 0){
      everyFiveMinutes();
    }
    
    if(enableWifiScanning && (oneHzCounter % wifiScanIntervalSeconds == 0 || oneHzCounter == 0)) {
      String wifiReport = scanWifiNetworks();
      Serial.print(wifiReport);
    }
    
    //sendDebugUDP();
    oneHzCounter++;
}

void checkOneHz(){
  unsigned long timeout = lastOneHz + ONE_HZ_INTERVAL;
  if(micros() > timeout){
    oneHz();
    lastOneHz = micros();
  }
}

void sixtyHz(){
  if(state == STATE_SLEEP){
      float counter = (double) sixtyHzCounter;
      counter = counter / SLEEP_BREATH_DIVISOR;
      float wave = cos(counter);
      if(wave < 0){
        wave = wave * -1;
      }
      double sleepBrightness = 255 * wave * SLEEP_BREATH_MAX_BRIGHTNESS_DIVISOR;
      ledColour(sleepBrightness, 0, sleepBrightness);
  }
  sixtyHzCounter++;
}

void checkSixtyHz(){
  unsigned long timeout = lastSixtyHz + SIXTY_HZ_INTERVAL;
  if(micros() > timeout){
    sixtyHz();
    lastSixtyHz = micros();
  }
}

void checkMotorHz(){
  
}

void timerCallback(void *pArg) {
      checkMotorHz();
      checkSixtyHz();
      tickOccured = true;
}

void setupTimers(){
  os_timer_setfn(&backgroundTaskTimer, timerCallback, NULL);
  os_timer_arm(&backgroundTaskTimer, 60, true);
}
