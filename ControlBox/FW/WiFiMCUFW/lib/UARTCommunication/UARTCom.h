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
    static bool DebugSwitch;
private:
    UARTCom();
    static void Println(String message);
    static int transmitDataToBuffer(byte* data, int numOfBytesToTransmit);
    static inline int getPositionToWrite();
    static void checkReceiveTimeout();
    static void receiveProcess();
    static bool validateBytes();
};
#endif