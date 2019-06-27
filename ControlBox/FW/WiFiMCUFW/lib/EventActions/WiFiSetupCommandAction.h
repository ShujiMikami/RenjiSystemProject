#ifndef _WIFISETUPCOMMANDACTION_H_
#define _WIFISETUPCOMMANDACTION_H_

#include <Arduino.h>
#include "CommandAction.h"

class WiFiSetupCommandAction : public CommandAction{
public:
    static const int eventCode = 1;
    static void (*GetCallBackPointer())();
private:
    static void callBack();
    WiFiSetupCommandAction();
};

#endif