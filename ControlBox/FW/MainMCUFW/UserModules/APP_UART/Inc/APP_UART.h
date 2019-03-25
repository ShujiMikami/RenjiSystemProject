#ifndef _APP_UART_H_
#define _APP_UART_H_

#include "stm32f3xx_hal.h"
#include "usart.h"

typedef enum{
    APP_UART_STANDBY,
    APP_UART_RUNNING,
    APP_UART_ERROR_STOPPED
}APP_UART_Stauts_t;

void StartUartRXTask(const void* argument);
void StartUartTXTask(const void* argument);
int UARTGetReceivedData(uint8_t* buffer, uint16_t bufferLength);
void UARTSendData(uint8_t* data, uint16_t dataLength);
void UARTInit();
APP_UART_Stauts_t GetStatus_APP_UART();




#endif