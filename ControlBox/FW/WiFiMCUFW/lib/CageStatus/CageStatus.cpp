#include "CageStatus.h"

const String ModeName[] = {
    "FullAuto",
    "SemiAuto",
    "FullManual",
    "NotDefined"
};

const String JudgeName[] = {
    "Heating",
    "NaturalCooling",
    "Cooling",
    "NotDefined"
};

CageStatus_t::ActivatedMode_t CageStatus_t::GetMode()
{
    return mode;
}
double CageStatus_t::GetTemperature()
{
    return temperature;
}
CageStatus_t::EnvironmentJudge_t CageStatus_t::GetEnvironmentJudge()
{
    return environmentJudge;
}
byte CageStatus_t::GetSwitchStatus()
{
    return switchStatus;
}
CageStatus_t::CageStatus_t()
{

}
CageStatus_t::CageStatus_t(CageStatus_t::ActivatedMode_t Mode, double Temperature, CageStatus_t::EnvironmentJudge_t EnvironmentJudge, byte SwitchStatus)
{
    mode = Mode;
    temperature = Temperature;
    environmentJudge = EnvironmentJudge;
    switchStatus = SwitchStatus;
}
String CageStatus_t::GetModeByString()
{
    return ModeName[(int)GetMode()];
}
String CageStatus_t::GetEnvironmentJudgeByString()
{
    return JudgeName[(int)GetEnvironmentJudge()];
}
CageStatus_t::CageStatus_t(byte Mode, double Temperature, byte EnvironmentJudge, byte SwitchStatus)
{
    switch(Mode){
    case (byte)FULL_AUTO : 
    case (byte)SEMI_AUTO : 
    case (byte)FULL_MANUAL : 
        mode = (ActivatedMode_t)Mode;
        break;
    default : 
        mode = NOT_DEFINED_MODE;
        break;
    }

    switch (EnvironmentJudge){
    case (byte)HEATING :
    case (byte)NATURAL_COOLING : 
    case (byte)COOLING : 
        environmentJudge = (EnvironmentJudge_t)EnvironmentJudge;
        break;
    default : 
        environmentJudge = NOT_DEFINED_JUDGE;
        break;
    }
}