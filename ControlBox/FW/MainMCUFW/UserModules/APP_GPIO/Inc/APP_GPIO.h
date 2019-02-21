#ifndef _APP_GPIO_H_
#define _APP_GPIO_H_
#endif


#include "stm32f3xx_hal.h"
#include "gpio.h"


typedef enum{
    TRUE,
    FALSE
}boolean_t;

void APP_GPIO_Init();
void APP_GPIO_Write(GPIO_TypeDef* gpioPort, uint16_t gpioPin, GPIO_PinState gpioState);
GPIO_PinState APP_GPIO_Read(GPIO_TypeDef* gpioPort, uint16_t gpioPin, boolean_t antiChattering);
void APP_GPIO_SetChatteringParam(uint32_t period_ms_to_set, uint32_t stableCount_to_set);