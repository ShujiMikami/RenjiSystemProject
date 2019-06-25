#ifndef _WIFISETTINGRECEIVEDCOMMAND_H_
#define _WIFISETTINGRECEIVEDCOMMAND_H_

#include "Command_t.h"
#include <Arduino.h>

class WiFiSettingReceivedCommand : public Command_t{
public:
    WiFiSettingReceivedCommand(byte* dataArray, size_t arrayLength);
    WiFiSettingReceivedCommand();
    static const byte CommandCode = 0x02;
private:
};
#endif