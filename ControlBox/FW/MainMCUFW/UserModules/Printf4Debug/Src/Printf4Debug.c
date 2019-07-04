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

static void startPrintfTask(const void* argument);
static Printf4Debug_Stauts_t taskStatus = Printf4Debug_STANDBY;

void Printf4Debug(const char* format, ...)
{
  if(taskStatus == Printf4Debug_RUNNING){
    //不定長変数の処理
    static char bufToSend[QUEUE_BUFFER_SIZE];

    va_list ap;

    va_start(ap, format);

    volatile int charLength = vsprintf(bufToSend, format, ap);

    va_end(ap);

    //データのQueueへの格納
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
}
void startPrintfTask(const void* argument)
{
  char buffer[QUEUE_SIZE];

  while(1){
    xQueueReceive(printfMessageQueue, buffer, portMAX_DELAY);

    if(HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 1000) != HAL_OK){
      taskStatus = Printf4Debug_ERROR_STOPPED;
    }

    if(taskStatus != Printf4Debug_RUNNING){
      break;
    }
  }
}
void PrintfInit()
{
  if(taskStatus != Printf4Debug_RUNNING){
    printfMessageQueue = xQueueCreate(QUEUE_DEPTH, QUEUE_SIZE);
    
    osThreadDef(PrintfTask, startPrintfTask, osPriorityNormal, 0, 128);
    PrintfTaskhandle = osThreadCreate(osThread(PrintfTask), NULL);

    if(PrintfTaskhandle != NULL){
      taskStatus = Printf4Debug_RUNNING;
    }
    else{
      taskStatus = Printf4Debug_ERROR_STOPPED;
    }
  }
}
Printf4Debug_Stauts_t GetStatus_Printf4Debug()
{
  return taskStatus;
}