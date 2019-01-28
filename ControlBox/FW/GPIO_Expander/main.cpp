#include "mbed.h"

#define I2C_SDA_PIN dp5
#define I2C_SCL_PIN dp27
#define I2C_SAD 0x5E
#define I2C_FREQ 100000



int main() {
    //Start I2C Slave
    I2CSlave i2cSlave(I2C_SDA_PIN, I2C_SCL_PIN);

    //AddressSetting
    i2cSlave.address(I2C_SAD);

    //FreqSetting
    i2cSlave.frequency(I2C_FREQ);
    


    while(1) {
    }
}
