#ifndef I2C_H
#define I2C_H

void setupI2C(){
  // i2c service startup
  Serial.printf("Starting i2c service on SDA=%d SCL=%d ... ", I2C_SDA, I2C_SCL);
  //Wire.begin(I2C_SDA, I2C_SCL);
  Serial.println("[DONE]");
}
void i2cScan(){
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning i2c bus...");
 
  nDevices = 0;
  for(address = 1; address < 255; address++ ) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    //Serial.printf("%#04x = %d\n", address, error);
 
    if (error == 0){
      Serial.printf("i2c device found at address %#04x!\n", address);
      nDevices++;
    } else if (error==4) {
      Serial.printf("Unknown error at address %#04x\n", address);
    }    
  }
  if (nDevices == 0){
    Serial.println("No I2C devices found\n");
  }else{
    Serial.println("done\n");
  }
}

bool i2cDeviceExists(byte address){
  Wire.beginTransmission(address);
   if (Wire.endTransmission() == 0){
    return true;
  }else{
    return false;   
  }
}

#endif
