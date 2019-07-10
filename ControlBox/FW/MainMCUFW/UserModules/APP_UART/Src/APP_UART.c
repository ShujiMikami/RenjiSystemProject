#include "APP_UART.h"
#include "cmsis_os.h"
#include "dma.h"

typedef struct{
  uint8_t* DataPointer;
  uint16_t DataLength;
}TXQueueStruct_t;

#define UART_RX_QUEUE_DEPTH 300
#define UART_TX_QUEUE_DEPTH 5
#define UART_RX_QUEUE_SIZE 1
#define UART_TX_QUEUE_SIZE sizeof(TXQueueStruct_t)
#define UART_RX_QUEUE_BUFFER_SIZE (UART_RX_QUEUE_DEPTH * UART_RX_QUEUE_SIZE)
#define UART_TX_QUEUE_BUFFER_SIZE (UART_TX_QUEUE_DEPTH * UART_TX_QUEUE_SIZE)

#define UART_RECEIVE_BUFFER_SIZE 127

osThreadId UartRXTaskHandle;
osThreadId UartTXTaskHandle;
xQueueHandle UartRxQueue;
xQueueHandle UartTxQueue;

static int bufferEdgePassCnt = 0;

static APP_UART_Stauts_t taskStatus = APP_UART_STANDBY;
static uint8_t receiveBuffer[UART_RECEIVE_BUFFER_SIZE];

static int queuedCount = 0;

void UARTInit()
{
  if(taskStatus != APP_UART_RUNNING){
    UartRxQueue = xQueueCreate(UART_RX_QUEUE_DEPTH, UART_RX_QUEUE_SIZE);
    UartTxQueue = xQueueCreate(UART_TX_QUEUE_DEPTH, UART_TX_QUEUE_SIZE);

    //RXTaskスタート
    osThreadDef(UARTRXTask, StartUartRXTask, osPriorityNormal, 0, 128);
    UartRXTaskHandle = osThreadCreate(osThread(UARTRXTask), NULL);

    //TXTaskスタート
    osThreadDef(UARTTXTask, StartUartTXTask, osPriorityNormal, 0, 128);
    UartTXTaskHandle = osThreadCreate(osThread(UARTTXTask), NULL);

    if(UartTXTaskHandle != NULL && UartRXTaskHandle != NULL){
      taskStatus = APP_UART_RUNNING;
    }
    else{
      taskStatus = APP_UART_ERROR_STOPPED;
    }
  }
}

void StartUartRXTask(const void* argument)
{

  HAL_UART_Receive_DMA(&huart1, receiveBuffer, sizeof(receiveBuffer));

  int readPosition = -1;
  int writePosition = -1;
  int dataCount = 0;

  while(1){

    volatile int edgePassed = bufferEdgePassCnt;
   
    volatile int lastDataPosition = UART_RECEIVE_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx) - 1;

    if(edgePassed == 0){//バッファがエッジに到達していない
      //この場合は, lastDataPosition >= readPositionしかありえない
      dataCount = lastDataPosition - readPosition;
    }
    else if(edgePassed == 1 && lastDataPosition <= readPosition){//読む前にデータが一度だけ満タンの場合は, read以前の場所しか許されない
      dataCount = lastDataPosition + UART_RECEIVE_BUFFER_SIZE - readPosition;
    }
    else{
      //bufferEdgeCount = 1で, readを超えた場合はバッファオーバーフロー
      //bufferEdgeCount > 1は, バッファオーバーフロー
      
      //エラー
      taskStatus = APP_UART_ERROR_STOPPED;
      bufferEdgePassCnt = 0;
    }

    if(taskStatus == APP_UART_ERROR_STOPPED){
      //エラー時は, タスクステータスをセットしてブレークすることでタスク終了してしまう
      //このフラグは, TXタスクで立つ場合もある
      //break;
      FlushBuffer();
    }
  
    int cnt = 0;
    for(cnt = 0; cnt < dataCount; cnt++){
      if(readPosition == UART_RECEIVE_BUFFER_SIZE - 1){
        bufferEdgePassCnt = 0;
      }
      readPosition = (readPosition + 1) % UART_RECEIVE_BUFFER_SIZE;
      xQueueSendToBack(UartRxQueue, &receiveBuffer[readPosition % UART_RECEIVE_BUFFER_SIZE], 0);
      queuedCount++;
    }   
  }
  osDelay(10);
}
void StartUartTXTask(const void* argument)
{
  TXQueueStruct_t queueStruct;

  while(1){
    if(xQueueReceive(UartTxQueue, &queueStruct, portMAX_DELAY) == pdTRUE){
      if(HAL_UART_Transmit(&huart1, queueStruct.DataPointer, queueStruct.DataLength, 1000) != HAL_OK){
        taskStatus = APP_UART_ERROR_STOPPED;
      }
    }

    if(taskStatus == APP_UART_ERROR_STOPPED){
      //エラー時は, タスクステータスをセットしてブレークすることでタスク終了してしまう
      //このフラグは, RXタスクで立つ場合もある
      FlushBuffer();
      //break;
    }
  }
  osDelay(10);
}
int UARTGetReceivedData(uint8_t* buffer, uint16_t bufferLength)
{
  int bufferedCount = 0;

  int cnt = 0;
  for(cnt = 0; cnt < bufferLength; cnt++){
    uint8_t tempBuf = 0;
    if(xQueueReceive(UartRxQueue, &tempBuf, 0) == pdTRUE){
      buffer[bufferedCount] = tempBuf;
      bufferedCount++;
      queuedCount--;
    }
  }

  return bufferedCount;
}
void UARTSendData(uint8_t* data, uint16_t dataLength)
{
  if(taskStatus == APP_UART_RUNNING){
    TXQueueStruct_t queueStruct;

    queueStruct.DataPointer = data;
    queueStruct.DataLength = dataLength;

    xQueueSendToBack(UartTxQueue, &queueStruct, portMAX_DELAY);
  }
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == &huart1){
    bufferEdgePassCnt++;
  }
}
APP_UART_Stauts_t GetStatus_APP_UART()
{
  return taskStatus;
}
int GetRxQueueCount()
{
  return queuedCount;
}
void FlushBuffer()
{
  xQueueReset(UartRxQueue);
  xQueueReset(UartTxQueue);

  queuedCount = 0;
}