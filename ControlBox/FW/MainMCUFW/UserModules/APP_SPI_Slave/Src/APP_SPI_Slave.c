#include "APP_SPI_Slave.h"
#include "cmsis_os.h"


static void start_SPI_Read_Task(const void* argument);

void APP_SPI_Slave_Init()
{
  uint8_t aTxBuffer[10] = {0};
  uint8_t aRxBuffer[10] = {0};
  
  HAL_SPI_Receive_DMA(&hspi1, aRxBuffer, sizeof(aRxBuffer));


}
void APP_SPI_Slave_SetData(uint8_t data)
{

}
void APP_SPI_SLAVE_GetData(uint8_t* buffer, uint16_t bufferSize)
{

}
uint16_t APP_SPI_SLAVE_GetDataCount()
{

}

void start_SPI_Read_Task(const void* argument)
{


}