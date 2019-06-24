#include "DebugPrintf.h"

bool PrintfDebugger::isInitialized = false;

const int DEBUG_BAUDRATE = 115200;

static HardwareSerial* pSerialForDebug = &Serial1;

void PrintfDebugger::Printf(String message)
{
    if(!isInitialized){
       pSerialForDebug->begin(115200); 
       isInitialized = true;
    }

    pSerialForDebug->print(message);
}
void PrintfDebugger::Println(String message)
{
    if(!isInitialized){
       pSerialForDebug->begin(115200); 
       isInitialized = true;
    }

    pSerialForDebug->println(message);
}