#include "mbed.h"

#define I2C_SDA_PIN dp5
#define I2C_SCL_PIN dp27
#define I2C_SAD 0x5E
#define I2C_FREQ 100000

#define SERIAL_BAUD_RATE 115200

//
Serial uart(USBTX, USBRX, SERIAL_BAUD_RATE);

//Start I2C Slave
I2CSlave i2cSlave(I2C_SDA_PIN, I2C_SCL_PIN);

void commandBuffering();

int main() 
{
    //AddressSetting
    i2cSlave.address(I2C_SAD);

    //FreqSetting
    i2cSlave.frequency(I2C_FREQ);

    while(1) {
        uart.printf("test\r\n");

        wait(1);
        
    }
}

void commandBuffering()
{
    int receivedStatus = i2cSlave.receive();

    switch (receivedStatus)
    {
        case I2CSlave::WriteAddressed :
            /* code */
            break;
        case I2CSlave::ReadAddressed : 
            /* code */
            break;
        default:
            break;
    }
}