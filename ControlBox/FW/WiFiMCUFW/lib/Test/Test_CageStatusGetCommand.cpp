#include "Test_CageStatusGetCommand.h"
#include "CageStatusGetCommand.h"
#include "DebugPrintf.h"


void CageStatusGetCommandTest::Setup()
{
    CageStatusGetCommand::DebugSwitch = true;

    PrintfDebugger::Println("################Constructor with dataArray and size####################");

    byte dataArray[67] = {0};
    dataArray[0] = 0x04;//動作モード
    dataArray[2] = 0x01;//CurrentTemp_H
    dataArray[3] = 0x02;//CurrentTemp_L
    dataArray[4] = 0x03;//Judgement
    dataArray[5] = 0x04;//Time_HH
    dataArray[6] = 0x05;//Time_HL
    dataArray[7] = 0x06;//Time_LH
    dataArray[8] = 0x07;//Time_LL
    dataArray[9] = 0x08;//SwStatus
    dataArray[66] = 0x28;

    CageStatusGetCommand command = CageStatusGetCommand(dataArray, sizeof(dataArray));

    byte activationMode = command.GetActivationMode();
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "activationMode = " + String(activationMode));

    uint16_t currentTemperature = command.GetCurrentTemperature();
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "currentTemperature = " + String(currentTemperature));
    
    byte envJudge = command.GetEnvironmentJudgement();
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "environmentJudgement = " + String(envJudge));

    uint32_t currentTime = command.GetInternalTime();
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "currentTime = " + String(currentTime));

    byte switchStatus = command.GetSwitchStatus();
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "switchStatus = " + String(switchStatus));



    PrintfDebugger::Println("##############Constructor with SSID and PASS############################");

    CageStatusGetCommand command2 = CageStatusGetCommand();
}
void CageStatusGetCommandTest::Loop()
{

}