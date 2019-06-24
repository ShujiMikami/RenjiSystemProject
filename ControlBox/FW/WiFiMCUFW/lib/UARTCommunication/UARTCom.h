#ifndef _UARTCOM_H_
#define _UARTCOM_H_

#include <Arduino.h>

class UARTCom{
public:
    static int GetReceivedCount();
    static int GetReceivedData(byte* buffer, int numOfBytesToRead);
    static void SendData(byte* data, int numOfBytesToSend);
    static void Setup();
    static void Loop();
private:
    UARTCom();
};
#endif