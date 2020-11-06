float ADC_value=0.0048828125;
float analogReading;

void ldr_task(void *pvParameter){

  sensorData data;
    while (1)
    {
      data = readLDR();
      sendQueue(&data);
      Serialprint("[INFO] LDR data sent\r");
      taskYIELD(); 
    }
}

sensorData readLDR(){
    sensorData data;
    data.type = ldr_sensor;
    analogReading = analogRead(LDR);
    data.analog.value = calculateLux(analogReading);
    Serialprint("[INFO] LDR | raw: %d | lux: %d \r", analogReading, data.analog.value);
    return data;
}

float calculateLux(float val){
  if (val != 0){
    return (250.000000/(ADC_value*val))-50.000000;
  }
  return 0.0;
}
