#ifndef _WIFISETUPCOMMAND_H_
#define _WIFISETUPCOMMAND_H_

#include "Command_t.h"
#include <Arduino.h>

class WiFiSetupCommand : public Command_t{
public:
    WiFiSetupCommand(byte* dataArray, size_t arrayLength);
    WiFiSetupCommand(byte* SSID, byte* PASS);
    static const byte CommandCode = 0x01;
    int GetSSID(byte* buffer, size_t bufferSize);
    int GetPass(byte* buffer, size_t bufferSize);
private:
};
#endif