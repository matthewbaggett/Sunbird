#define ADC_SAMPLE_EN 5
int adcValue;

bool sample_adc_en = false;

void setupADC(){
  pinMode(ADC_SAMPLE_EN, OUTPUT);
}

void ADCDisableSample(){
  sample_adc_en = false;
  //Serial.println("Disabling ADC Sampling transistor.");
  digitalWrite(ADC_SAMPLE_EN, LOW);  
}

void ADCEnableSample(){
  sample_adc_en = true;
  //Serial.println("Enabling ADC Sampling transistor.");
  digitalWrite(ADC_SAMPLE_EN, HIGH);  
}

void ADCToggleSample(){
  if(sample_adc_en){
    ADCDisableSample();
  }else{
    ADCEnableSample();
  }
}

int updateADC(){
  ADCEnableSample();
  adcValue = analogRead(A0);
  ADCDisableSample();
  return adcValue;
}

