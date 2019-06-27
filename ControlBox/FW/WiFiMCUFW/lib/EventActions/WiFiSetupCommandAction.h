#ifndef _WIFISETUPCOMMANDACTION_H_
#define _WIFISETUPCOMMANDACTION_H_

#include <Arduino.h>

class WiFiSetupCommandAction{
public:
    static const int eventCode = 1;
    static void (*GetCallBackPointer())();
    static bool DebugSwitch;
private:
    static void callBack();
    WiFiSetupCommandAction();
    static void Println(String message);
};

#endif