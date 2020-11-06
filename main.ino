#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <LiquidCrystal.h>
#include <dht.h>
#include <semphr.h>
#include <MemoryFree.h>

#define RST 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
#define LDR A0
#define DHT22PIN 6

enum sensor_msg_type {dht_sensor, ldr_sensor};

typedef struct {
  bool valid;
  long temp;
  long humidity;
} dhtData;

typedef struct {
  float value;
} analogData;

typedef struct {
  enum sensor_msg_type type;
  union {
    dhtData dht;
    analogData analog;
  };
} sensorData;

QueueHandle_t queue_1;
SemaphoreHandle_t xMutex;
BaseType_t xReturned;
LiquidCrystal lcd(RST, EN, D4, D5, D6, D7);

void setup()
{
  Serial.begin(9600);
  checkMemory();
  lcd.begin(16, 4);
  lcd.print("-FREERTOS JAMUR-");

  initRTOS();
}

void StreamPrint_progmem(Print &out, PGM_P format, ...)
{
  char formatString[128], *ptr;
  strncpy_P( formatString, format, sizeof(formatString) ); 
  formatString[ sizeof(formatString) - 2 ] = '\0';
  ptr = &formatString[ strlen(formatString) + 1 ]; // our result buffer...
  va_list args;
  va_start (args, format);
  vsnprintf(ptr, sizeof(formatString) - 1 - strlen(formatString), formatString, args );
  va_end (args);
  formatString[ sizeof(formatString) - 1 ] = '\0';
  out.print(ptr);
}
#define Serialprint(format, ...) StreamPrint_progmem(Serial,PSTR(format),##__VA_ARGS__)
#define Streamprint(stream,format, ...) StreamPrint_progmem(stream,PSTR(format),##__VA_ARGS__)

void loop() {}
