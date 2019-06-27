#include "CommandAction.h"
#include "DebugPrintf.h"

bool CommandAction::DebugSwitch = false;

void CommandAction::Println(String message)
{
    if(DebugSwitch){
        PrintfDebugger::Println(message);
    }
}