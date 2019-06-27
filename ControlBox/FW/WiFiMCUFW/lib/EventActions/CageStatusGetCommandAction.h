#ifndef _CAGESTATUSGETCOMMANDACTION_H_
#define _CAGESTATUSGETCOMMANDACTION_H_

#include <Arduino.h>
#include "CommandAction.h"

class CageStatusGetCommandAction : public CommandAction{
public:
    static void (*GetCallBackPointer())();
private:
    static void callBack();
    CageStatusGetCommandAction();
};

#endif