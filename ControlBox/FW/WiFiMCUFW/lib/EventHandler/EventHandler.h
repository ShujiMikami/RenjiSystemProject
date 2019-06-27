#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include <Arduino.h>

class EventHandler{
public:
    static void Setup();
    static bool RegisterEvent(int eventCode, void (*callBack)());
    static void ExecuteEvent(int eventCode);
    static bool DebugSwitch;
private:
    EventHandler();
    static bool checkEventCodeRegisterable(int eventCode);
    static void Println(String message);
    static bool isCallBackRegistered(int eventCode);
};

#endif