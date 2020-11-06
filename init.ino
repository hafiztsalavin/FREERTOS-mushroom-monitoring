void initRTOS(){
    createMutex();
    createQueue();
    createTask();
}
void createMutex(){
  xMutex = xSemaphoreCreateMutex();
    if (xMutex == NULL){
      Serialprint("[ERROR] Can't create mutex \r");
    } else{
      Serialprint("[INFO] Mutex created \r");  
    }
    //checkMemory();
}

void createQueue(){
    Serialprint("[INFO] Creating queue with size of %d\r",sizeof(sensorData));
    queue_1 = xQueueCreate(4, sizeof(sensorData));
    if (queue_1 == NULL)
    {
        Serialprint("[ERROR] Can't create queue \r");
    }
    Serialprint("[INFO] Queue created\r");
    //checkMemory();
}

void createTask(){
    xReturned = xTaskCreate(lcd_task, "LCD TASK", 128, NULL, 1, NULL);
    checkTaskCreation("LCD", xReturned);
    
    xReturned = xTaskCreate(dht22_task, "DHT22 TASK", 128, NULL, 3, NULL);
    checkTaskCreation("dht22" ,xReturned);
    
    xReturned = xTaskCreate(ldr_task, "LDR TASK", 128, NULL, 3, NULL);
    checkTaskCreation("LDR", xReturned);

    vTaskStartScheduler();
    //checkMemory();
    Serialprint("[INFO] Task schedule started \n");
}

void checkTaskCreation(String task_name, BaseType_t xReturned){
  if (xReturned == pdPASS){
    Serialprint("[INFO] created %s task \r", task_name);
  } else if (xReturned == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
    Serialprint("[ERROR] Can't create Task, memory allocation error \r");
  }else{
    Serialprint("[ERROR] Create task unknown error \r");
  }
  //checkMemory();
}
