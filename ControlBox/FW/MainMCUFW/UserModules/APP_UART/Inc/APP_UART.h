#ifndef _APP_UART_H_
#define _APP_UART_H_

#include "stm32f3xx_hal.h"
#include "usart.h"


void StartUartRXTask(const void* argument);
void StartUartTXTask(const void* argument);
int UARTGetReceivedData(uint8_t* buffer, uint16_t bufferLength);
void UARTSendData(uint8_t* data, uint16_t dataLength);
void UARTInit();





#endif