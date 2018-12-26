#define LED_RED 14
#define LED_GREEN 2
#define LED_BLUE 16

int current_red;
int current_green;
int current_blue;

void ledColour(int red, int green, int blue){
  current_red = red;
  current_green = green;
  current_blue = blue;
  int red_output = PWMRANGE - (red*(PWMRANGE/255)) ;
  int green_output = PWMRANGE - (green*(PWMRANGE/255));
  int blue_output = PWMRANGE - (blue*(PWMRANGE/255));
  
  /*Serial.print("LED: (");
  Serial.print(red_output);
  Serial.print(",");
  Serial.print(green_output);
  Serial.print(",");
  Serial.print(blue_output);
  Serial.println(")");*/

  analogWrite(LED_RED, red_output);
  analogWrite(LED_GREEN, green_output);
  analogWrite(LED_BLUE, blue_output);
}

void testFade(){
  int brightness = 0;
  int fadeAmount = 25;
  while(true){
    Serial.println(brightness);
    analogWrite(LED_RED, brightness);
    brightness = brightness + fadeAmount;
  
    if (brightness <= 0 || brightness >= PWMRANGE) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}

void testLed(){
  while(true){
    Serial.println("Red");
    ledColour(255,0,0);
    delay(1500);
    Serial.println("Green");
    ledColour(0,255,0);
    delay(1500);
    Serial.println("Blue");
    ledColour(0,0,255);
    delay(1500);
    Serial.println("Off");
    ledColour(0,0,0);
    delay(1500);
    Serial.println("Red Dim");
    ledColour(50,0,0);
    delay(1500);
    Serial.println("Green Dim");
    ledColour(0,50,0);
    delay(1500);
    Serial.println("Blue Dim");
    ledColour(0,0,50);
    delay(1500);
    Serial.println("Off");
    ledColour(0,0,0);
    delay(1500);
  }
}
void setupPWM(){
  // PWM service startup
  ////console.printf("Start PWM@%dhz: ", pwmHz);
  analogWriteFreq(pwmHz);
  ////console.println("[OK]");
}
void setupLed(){
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
}
