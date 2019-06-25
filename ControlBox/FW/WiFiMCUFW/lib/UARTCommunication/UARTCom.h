#ifndef _UARTCOM_H_
#define _UARTCOM_H_

#include <Arduino.h>

class UARTCom{
public:
    static bool NewCommandAvailable();
    static int GetReceivedData(byte* buffer, size_t bufferSize);
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
//    static bool validateBytes();
};
#endif