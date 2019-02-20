#include "Printf4Debug.h"

#include "stm32f3xx_hal.h"
#include "cmsis_os.h"
#include "usart.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define QUEUE_DEPTH 10
#define QUEUE_SIZE 20
#define QUEUE_BUFFER_SIZE (QUEUE_DEPTH * QUEUE_SIZE)


xQueueHandle printfMessageQueue;
osThreadId PrintfTaskhandle;

void Printf4Debug(const char* format, ...)
{
  static char bufToSend[QUEUE_BUFFER_SIZE];

  va_list ap;

  va_start(ap, format);

  volatile int charLength = sprintf(bufToSend, format, ap);

  va_end(ap);

  volatile int queueCount = charLength / QUEUE_SIZE;

  if((charLength % QUEUE_SIZE) != 0){
    queueCount += 1;
  }

  int cnt = 0;

  for(cnt = 0; cnt < queueCount; cnt++){
    char bufPart[QUEUE_SIZE];
    strncpy(bufPart, &bufToSend[(QUEUE_SIZE - 1) * cnt], (QUEUE_SIZE - 1));
    bufPart[QUEUE_SIZE - 1] = '\0';

    xQueueSendToBack(printfMessageQueue, bufPart, portMAX_DELAY);
  }
}
void StartPrintfTask(const void* argument)
{
  char buffer[QUEUE_SIZE];

  while(1){
    xQueueReceive(printfMessageQueue, buffer, portMAX_DELAY);

    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000);
  }
}

void PrintfInit()
{
    printfMessageQueue = xQueueCreate(QUEUE_DEPTH, QUEUE_SIZE);
    
    osThreadDef(PrintfTask, StartPrintfTask, osPriorityNormal, 0, 128);
    PrintfTaskhandle = osThreadCreate(osThread(PrintfTask), NULL);
}