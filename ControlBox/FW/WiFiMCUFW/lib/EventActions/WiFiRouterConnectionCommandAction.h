#ifndef _WIFIROUTERCONNECTIONCOMMANDACTION_H_
#define _WIFIROUTERCONNECTIONCOMMANDACTION_H_

#include <Arduino.h>
#include "CommandAction.h"

class WiFiRouterConnectionCommandAction : public CommandAction{
public:
    static const int eventCode = 1;
    static void (*GetCallBackPointer())();
private:
    static void callBack();
    WiFiRouterConnectionCommandAction();
};

#endif