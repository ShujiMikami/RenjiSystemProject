#ifndef _WIFISETTINGRECEIVEDCOMMANDACTION_H_
#define _WIFISETTINGRECEIVEDCOMMANDACTION_H_

#include <Arduino.h>
#include "CommandAction.h"

class WiFiSettingReceivedCommandAction : public CommandAction{
public:
    static void (*GetCallBackPointer())();
private:
    static void callBack();
    WiFiSettingReceivedCommandAction();
};

#endif