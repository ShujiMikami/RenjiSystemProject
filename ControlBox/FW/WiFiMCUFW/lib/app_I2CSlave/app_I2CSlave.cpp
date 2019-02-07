#include <Arduino.h>
#include <Wire.h>

#define MAX_RECIEVE_BUF_SIZE 255

static const uint8_t SLAVE_ADDRESS = 8;

static void receiveHandler();
static uint8_t buffer[MAX_RECIEVE_BUF_SIZE] = {0};
static uint8_t bufferdLength = 0;

void I2CSlaveTask_initialize()
{
    Wire.begin(8);
    //Wire.onRequest(receiveHandler);

}
void I2CSlaveTask_loop()
{
    if(Wire.available){
        buffer[bufferdLength++] = (uint8_t)Wire.read();
    }
}
void receiveHandler()
{
    while(Wire.available()){
        buffer[bufferdLength++] = (uint8_t)Wire.read();
    }
}