#ifndef _CAGESTATUSGETCOMMAND_H_
#define _CAGESTATUSGETCOMMAND_H_

#include "Command_t.h"
#include <Arduino.h>

class CageStatusGetCommand : public Command_t{
public:
    CageStatusGetCommand(byte* dataArray, size_t arrayLength);
    CageStatusGetCommand();
    CageStatusGetCommand(Command_t command);
    byte GetActivationMode();
    uint16_t GetCurrentTemperature();
    byte GetEnvironmentJudgement();
    uint32_t GetInternalTime();
    byte GetSwitchStatus();
    static const byte CommandCode = 0x04;
private:
};
#endif