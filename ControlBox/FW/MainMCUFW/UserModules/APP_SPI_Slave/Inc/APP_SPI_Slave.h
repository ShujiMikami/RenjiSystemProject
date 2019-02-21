#ifndef _APP_SPI_SLAVE_H_
#define _APP_SPI_SLAVE_H_
#endif

#include "stm32f3xx_hal.h"
#include "spi.h"

void APP_SPI_Slave_Init();
void APP_SPI_Slave_SetData(uint8_t data);
void APP_SPI_SLAVE_GetData(uint8_t* buffer, uint16_t bufferSize);
uint16_t APP_SPI_SLAVE_GetDataCount();