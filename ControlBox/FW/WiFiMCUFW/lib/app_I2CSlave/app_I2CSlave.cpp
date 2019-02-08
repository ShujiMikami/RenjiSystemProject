#include <Arduino.h>
#include <Wire.h>

#define THREAD_NAME "I2C_SLAVE_THREAD"


#define MAX_RECIEVE_BUF_SIZE 255

static const uint8_t SLAVE_ADDRESS = 8;

static void receiveHandler();
static uint8_t buffer[MAX_RECIEVE_BUF_SIZE] = {0};
static uint8_t bufferdLength = 0;

void I2CSlaveTask_initialize()
{
    Wire.begin(SLAVE_ADDRESS);
    //Wire.onRequest(receiveHandler);

}
void I2CSlaveTask_loop()
{
    
    if(Wire.available() > 0){
        buffer[bufferdLength++] = (uint8_t)Wire.read();
        Serial.print(THREAD_NAME);
        Serial.println(buffer[bufferdLength - 1]);
    }
    
}
void receiveHandler()
{
    /*
    while(Wire.available()){
        buffer[bufferdLength++] = (uint8_t)Wire.read();
    }
    Serial.println(THREAD_NAME);
    */
}