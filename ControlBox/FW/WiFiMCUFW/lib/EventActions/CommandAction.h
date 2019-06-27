#ifndef _COMMANDACTION_H_
#define _COMMANDACTION_H_

#include <Arduino.h>

class CommandAction{
public:
    static bool DebugSwitch;
protected:
    static void Println(String message);
};


#endif