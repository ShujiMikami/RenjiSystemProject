#ifndef _DEBUGPRINTF_H_
#define _DEBUGPRINTF_H_

#define DEBUG_MESSAGE_HEADER ("[file:" + String(__FILE__) + "]" + "[line:" + String(__LINE__) + "]")

#include <Arduino.h>

class PrintfDebugger{
public:
    static void Println(String message);
    static void Printf(String message);
private:
    static bool isInitialized;
    PrintfDebugger();
};



#endif