#ifndef _APP_Master_H_
#define _APP_Master_H_

#include <Arduino.h>
#include <SPI.h>

void SPIMasterTask_initialize();
void SPIMasterTask_loop();
void SPIMaster_initialize(const uint8_t slavePin, SPISettings setting);
void SPIMasterSendRead(uint8_t* sendData, uint8_t* receiveBuf, uint16_t dataLength);


#endif