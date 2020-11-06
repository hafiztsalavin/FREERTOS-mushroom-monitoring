void sendQueue(sensorData *data){
  Serialprint("[INFO] Trying to send data\r"); 
  xSemaphoreTake(xMutex, portMAX_DELAY);
  xQueueSend(queue_1, &data, portMAX_DELAY); 
  xSemaphoreGive(xMutex);
  Serialprint("[INFO] Size of queue %d\r", sizeof(queue_1)); 
}
