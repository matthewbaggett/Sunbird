#define DRV_A 13
#define DRV_B 12

int lastDirection = DRV_A;

void setupMotor(){
  pinMode(DRV_A, OUTPUT);
  pinMode(DRV_B, OUTPUT);
}

void motorKick(int motor){
  digitalWrite(motor, HIGH);
  delay(5);
  digitalWrite(motor, LOW);
}

void motorOn(int percentage){
  float percent = (float) percentage;
  Serial.print("Motor on ");
  Serial.print(percentage);
  Serial.print("% ");
  float power = PWMRANGE * (percent/100);
  Serial.print("(");
  Serial.print(power);
  Serial.print(") ");
  if(lastDirection == DRV_B){
    motorKick(DRV_A);
    analogWrite(DRV_A, power);
    analogWrite(DRV_B, 0);
    digitalWrite(DRV_B, LOW);
    lastDirection = DRV_A;
    Serial.println("Clockwise");
  }else{
    motorKick(DRV_B);
    analogWrite(DRV_B, power);
    analogWrite(DRV_A, 0);
    digitalWrite(DRV_A, LOW);
    lastDirection = DRV_B;
    Serial.println("Anti-Clockwise");
  } 
}

void motorOff(){
  motorOn(0);
}

void testMotor(){
  analogWriteFreq(pwmHz);
  for(int power = 0; power <= 100; power = power + 10){
    motorOn(power);
    delay(500);
  }
  
  Serial.print("Direct Drive...");
  digitalWrite(DRV_B, HIGH);
  delay(5000);
  digitalWrite(DRV_B, LOW);
  Serial.println(" vs motorOn(100)");
  motorOn(100);
  delay(5000);
  motorOn(0);
  Serial.println("Motor test done");
}
