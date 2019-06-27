#ifndef _UARTCOM_H_
#define _UARTCOM_H_

#include <Arduino.h>
#include "Command_t.h"

class UARTCom{
public:
    static void SendDataAndReceive(byte* data, size_t numOfBytesToSend, byte* receiveBuffer, size_t numOfBytesToReceive, int timeOut);
    static Command_t SendDataAndReceive(Command_t command, int timeOut);
    static void Setup();
    static bool DebugSwitch;
private:
    UARTCom();
    static void Println(String message);
};
#endif