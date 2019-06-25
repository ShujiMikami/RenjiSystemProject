#include "Test_WiFiSettingReceivedCommand.h"
#include "WiFiSettingReceivedCommand.h"
#include "DebugPrintf.h"


void WiFiSettingReceivedCommandTest::Setup()
{
    Command_t::DebugSwitch = true;

    PrintfDebugger::Println("################Constructor with dataArray and size####################");

    byte dataArray[67] = {0};
    dataArray[0] = 0x02;
    dataArray[66] = 0x02;

    WiFiSettingReceivedCommand command = WiFiSettingReceivedCommand(dataArray, sizeof(dataArray));

    PrintfDebugger::Println("##############Constructor with nothing############################");

    WiFiSettingReceivedCommand command2 = WiFiSettingReceivedCommand();

}
void WiFiSettingReceivedCommandTest::Loop()
{

}