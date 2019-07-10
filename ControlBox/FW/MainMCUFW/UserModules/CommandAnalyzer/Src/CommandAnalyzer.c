#include "CommandAnalyzer.h"
#include "cmsis_os.h"
#include "APP_UART.h"

#define COMMAND_BYTE_SIZE 67

static void commandAnalyzeTask();
void CommandAnalyzer_Init()
{
    osThreadId commandAnalyzerTaskID;

    osThreadDef(CommandAnalyzeTask, commandAnalyzeTask, osPriorityNormal, 0, 128);
    commandAnalyzerTaskID = osThreadCreate(osThread(CommandAnalyzeTask), NULL);

}
void commandAnalyzeTask()
{
    //UARTスレッドがちゃんと走るの待ち
    while(GetStatus_APP_UART() != APP_UART_RUNNING);

    int isReceiveStarted = 0;

    int timeoutCnt = 0;

    while(1){
        if(timeoutCnt > 10){
            FlushBuffer();
            timeoutCnt = 0;
            isReceiveStarted = 0;
        }

        int receivedByteCount = GetRxQueueCount();

        if(isReceiveStarted == 0 && receivedByteCount > 0){
            isReceiveStarted = 1;
        }

        if(receivedByteCount >= COMMAND_BYTE_SIZE){
            uint8_t buffer[90];
            UARTGetReceivedData(buffer, COMMAND_BYTE_SIZE);
            UARTSendData(buffer, COMMAND_BYTE_SIZE);
            Printf4Debug("%d bytes received\r\n", receivedByteCount);
        }

        if(isReceiveStarted == 1){
            timeoutCnt++;
        }

        osDelay(10);
      }
}