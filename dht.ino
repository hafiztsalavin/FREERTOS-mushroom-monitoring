dht DHT;

void dht22_task(void *pvParameters)
{
  sensorData data;
  for (;;)
  {
    data = read_dht22();
    if (data.dht.valid == true) {
      sendQueue(&data);
      Serialprint("[INFO] DHT data sent\r");
    }
    taskYIELD();
  }

}

sensorData read_dht22()
{
  sensorData data;
  int chk = DHT.read22(DHT22PIN);
  if (chk != 0) {
    Serialprint("[ERROR] Read dht22 error: %d \r", chk);
    data.dht.valid = false;
    return data;
  }
  else {
    data.type = dht_sensor;
    data.dht.temp = (float)DHT.temperature;
    data.dht.humidity = (float)DHT.humidity;
    data.dht.valid = true;
    Serialprint("[INFO] temp %d | humidity %d\r", data.dht.temp, data.dht.humidity);
    delay(100);
    return data;
  };
}
