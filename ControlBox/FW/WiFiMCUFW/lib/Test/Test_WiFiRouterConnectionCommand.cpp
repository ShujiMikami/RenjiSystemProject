#include "Test_WiFiRouterConnectionCommand.h"
#include "WiFiRouterConnectionCommand.h"
#include "DebugPrintf.h"


void WiFiRouterConnectionCommandTest::Setup()
{
    WiFiRouterConnectionCommand::DebugSwitch = true;

    PrintfDebugger::Println("################Constructor with dataArray and size####################");

    byte dataArray[67] = {0};
    dataArray[0] = 0x03;
    dataArray[66] = 0x03;

    WiFiRouterConnectionCommand command = WiFiRouterConnectionCommand(dataArray, sizeof(dataArray));

    byte connectionStatus = command.GetConnectionStatus();
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "connectionStatus = " + String(connectionStatus));

    PrintfDebugger::Println("##############Constructor with SSID and PASS############################");

    byte dataOfStatus = 0;

    WiFiRouterConnectionCommand command2 = WiFiRouterConnectionCommand(dataOfStatus);

}
void WiFiRouterConnectionCommandTest::Loop()
{

}