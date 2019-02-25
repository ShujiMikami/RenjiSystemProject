#include <Arduino.h>
#include <SPI.h>

#include "app_SPIMaster.h"

const uint8_t SLAVE_SELECT_PIN = 5;

SPISettings settings = SPISettings(100000, MSBFIRST, SPI_MODE0);

const uint8_t testBytes[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0 };
uint8_t rxBytes[12];
const uint8_t testBytes2[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0 };
const int sendBytes = 10;


void SPIMasterTask_initialize()
{
    pinMode(SLAVE_SELECT_PIN, OUTPUT);
    digitalWrite(SLAVE_SELECT_PIN, HIGH);
    SPI.begin(); 
}
void SPIMasterTask_loop()
{
    static int flag = 0;


    SPI.beginTransaction(settings);

    digitalWrite(SLAVE_SELECT_PIN, LOW);
    if(flag == 0){
        SPI.transferBytes((uint8_t*)testBytes, (uint8_t*)rxBytes, sendBytes);
        flag = 1;
    }else{
        SPI.transferBytes((uint8_t*)testBytes2, (uint8_t*)rxBytes, sendBytes);
        flag = 0;
    }
    digitalWrite(SLAVE_SELECT_PIN, HIGH);

    SPI.endTransaction();


    delay(1000);
}
void SPIMasterSendRead(uint8_t* sendData, uint8_t* receiveBuf, uint16_t dataLength)
{

}
void SPIMaster_initialize(const uint8_t slavePin, SPISettings setting)
{

}