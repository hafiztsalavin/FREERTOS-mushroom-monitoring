void lcd_task(void *pvParameter)
{
    sensorData data;
    while (1)
    {
        Serialprint("[INFO] LCD TASK");
        if (xQueueReceive(queue_1, &data, portMAX_DELAY) == pdPASS)
        {   
            Serialprint("[INF0] received: \r");
            Serialprint("temp %d | humidity %d\r", data.dht.temp, data.dht.humidity);  

        }
        taskYIELD();
    }
}
