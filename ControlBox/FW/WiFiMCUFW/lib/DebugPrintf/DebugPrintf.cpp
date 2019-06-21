#include "DebugPrintf.h"

bool PrintfDebugger::isInitialized = false;

const int DEBUG_BAUDRATE = 115200;

static HardwareSerial serialForDebug = Serial1;

void PrintfDebugger::Printf(String message)
{
    if(!isInitialized){
       serialForDebug.begin(115200); 
       isInitialized = true;
    }

    serialForDebug.print(message);
}
void PrintfDebugger::Println(String message)
{
    if(!isInitialized){
       serialForDebug.begin(115200); 
       isInitialized = true;
    }

    serialForDebug.println(message);
}