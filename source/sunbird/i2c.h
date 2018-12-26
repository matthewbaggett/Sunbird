
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

