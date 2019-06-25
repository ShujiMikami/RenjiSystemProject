#ifndef _WIFIROUTERCONNECTIONCOMMAND_H_
#define _WIFIROUTERCONNECTIONCOMMAND_H_

#include "Command_t.h"
#include <Arduino.h>

class WiFiRouterConnectionCommand : public Command_t{
public:
    WiFiRouterConnectionCommand(byte* dataArray, size_t arrayLength);
    WiFiRouterConnectionCommand(byte connectionStatus);
    static const byte CommandCode = 0x03;
    byte GetConnectionStatus();
private:
};
#endif