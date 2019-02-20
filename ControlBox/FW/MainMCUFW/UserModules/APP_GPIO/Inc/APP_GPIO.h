#ifndef _APP_GPIO_H_
#define _APP_GPIO_H_
#endif


#include "stm32f3xx_hal.h"
#include "gpio.h"

void APP_GPIO_Init();
void APP_GPIO_Write(GPIO_TypeDef* gpioPort, uint16_t gpioPin, GPIO_PinState gpioState);
GPIO_PinState APP_GPIO_Read(GPIO_TypeDef* gpioPort, uint16_t gpioPin, bool antiChattering);
void APP_GPIO_SetChatteringParam(uint32_t period_ms, uint32_t stableCount);