#ifndef _CAGESTATUSGETCOMMAND_H_
#define _CAGESTATUSGETCOMMAND_H_

#include "Command_t.h"
#include <Arduino.h>

class CageStatusGetCommand : public Command_t{
public:
typedef enum{
    FULL_AUTO = 0,
    SEMI_AUTO,
    FULL_MANUAL,
    NOT_DEFINED_MODE
}Activation_Mode_t;
typedef enum {
    HEATING = 0,
    NATURAL_COOLING,
    COOLING,
    NOT_DEFINED_JUDGE
}EnvironmentJudgement_t;

public:
    CageStatusGetCommand(byte* dataArray, size_t arrayLength);
    CageStatusGetCommand();
    CageStatusGetCommand(Command_t command);
    Activation_Mode_t GetActivationMode();
    double GetCurrentTemperature();
    EnvironmentJudgement_t GetEnvironmentJudgement();
    uint32_t GetInternalTime();
    byte GetSwitchStatus();
    static const byte CommandCode = 0x04;
    String GetActivationModeString();
    String GetEnvironmentJudgeString();
private:
};
#endif