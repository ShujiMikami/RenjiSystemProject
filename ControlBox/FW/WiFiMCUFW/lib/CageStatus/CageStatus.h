#ifndef CAGESTATUS_H_
#define CAGESTATUS_H_

#include <Arduino.h>

class CageStatus_t{
public:
    typedef enum{
        FULL_AUTO = 0,
        SEMI_AUTO,
        FULL_MANUAL,
        NOT_DEFINED_MODE
    }ActivatedMode_t;

    typedef enum{
        HEATING = 0,
        NATURAL_COOLING,
        COOLING,
        NOT_DEFINED_JUDGE        
    }EnvironmentJudge_t;
public:
    ActivatedMode_t GetMode();
    String GetModeByString();
    double GetTemperature();
    EnvironmentJudge_t GetEnvironmentJudge();
    String GetEnvironmentJudgeByString();
    byte GetSwitchStatus();
    CageStatus_t();
    CageStatus_t(ActivatedMode_t Mode, double Temperature, EnvironmentJudge_t EnvironmentJudge, byte SwitchStatus);
    CageStatus_t(byte Mode, double Temperature, byte EnvironmentJudge, byte SwitchStatus);
private:
    ActivatedMode_t mode;
    double temperature;
    EnvironmentJudge_t environmentJudge;
    byte switchStatus;
};
#endif