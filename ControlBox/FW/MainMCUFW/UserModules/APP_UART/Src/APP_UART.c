#include "APP_UART.h"
#include "cmsis_os.h"
#include "dma.h"

#define UART_RX_QUEUE_DEPTH 300
#define UART_TX_QUEUE_DEPTH 5
#define UART_RX_QUEUE_SIZE 1
#define UART_TX_QUEUE_SIZE 20
#define UART_RX_QUEUE_BUFFER_SIZE (UART_RX_QUEUE_DEPTH * UART_RX_QUEUE_SIZE)
#define UART_TX_QUEUE_BUFFER_SIZE (UART_TX_QUEUE_DEPTH * UART_TX_QUEUE_SIZE)


osThreadId UartRXTaskHandle;
osThreadId UartTXTaskHandle;
xQueueHandle UartRxQueue;
xQueueHandle UartTxQueue;

static int bufferEdgePassCnt = 0;

void UARTInit()
{
  UartRxQueue = xQueueCreate(UART_RX_QUEUE_DEPTH, UART_RX_QUEUE_SIZE);
  UartTxQueue = xQueueCreate(UART_TX_QUEUE_DEPTH, UART_TX_QUEUE_SIZE);
  
  //RXTaskスタート
  osThreadDef(UARTRXTask, StartUartRXTask, osPriorityNormal, 0, 128);
  UartRXTaskHandle = osThreadCreate(osThread(UARTRXTask), NULL);

  //TXTaskスタート
  osThreadDef(UARTTXTask, StartUartTXTask, osPriorityNormal, 0, 128);
  UartTXTaskHandle = osThreadCreate(osThread(UARTTXTask), NULL);
}
void StartUartRXTask(const void* argument)
{
  static uint8_t receiveBuffer[40];

  HAL_UART_Receive_DMA(&huart1, receiveBuffer, sizeof(receiveBuffer));

  int readPosition = 0;
  int writePosition = 0;
  int dataCount = 0;

  while(1){
    int lastDataPosition = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);

    if(lastDataPosition > readPosition){//データ書き込み位置がバッファ内で最後に読んだ場所よりも上位にある
      dataCount = lastDataPosition - readPosition;
    }
    else if(lastDataPosition < readPosition){//データ書き込み位置がバッファの終端を超えてしまった場合
      dataCount = lastDataPosition + 40 - readPosition;
    }
    else{//データ書き込み位置に変化がない場合
      //Do nothing
    }
   
    int cnt = 0;
    for(cnt = 0; cnt < dataCount; cnt++){
      xQueueSendToBack(UartRxQueue, &receiveBuffer[(readPosition + cnt) % 40], 0);
    }   
  }
}
void StartUartTXTask(const void* argument)
{
  char buffer[UART_TX_QUEUE_BUFFER_SIZE];

  while(1){
    xQueueReceive(UartTxQueue, buffer, portMAX_DELAY);

    HAL_UART_Transmit(&huart1, (uint8_t*)buffer, strlen(buffer), 1000);
  }
}
int UARTGetReceivedData(uint8_t* buffer, uint16_t bufferLength)
{
  int result = 0;

  int cnt = 0;
  for(cnt = 0; cnt < bufferLength; cnt++){
    xQueueReceive(UartRxQueue, buffer, 0);
  }

}
void UARTSendData(uint8_t* data, uint16_t dataLength)
{}
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart)
{
  bufferEdgePassCnt++;
}