#include "Test_WiFiSetupCommand.h"
#include "WiFiSetupCommand.h"
#include "DebugPrintf.h"


void WiFiSetupCommandTest::Setup()
{
    WiFiSetupCommand::DebugSwitch = true;

    PrintfDebugger::Println("################Constructor with dataArray and size####################");

    byte dataArray[67] = {0};
    dataArray[0] = 0x01;
    dataArray[66] = 0x01;

    WiFiSetupCommand command = WiFiSetupCommand(dataArray, sizeof(dataArray));

    byte buffer4SSID[32];
    byte buffer4PASS[32];
    
    int result = command.GetSSID(buffer4SSID, sizeof(buffer4SSID));
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "GetSSIDResult = " + String(result));

    result = command.GetPass(buffer4PASS, sizeof(buffer4PASS));
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "GetPASSResult = " + String(result));

    
    String message = "";
    for(int i = 0; i < 32; i++){
        message += String(buffer4SSID[i]) + ",";
    }
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + message);

    message = "";
    for(int i = 0; i < 32; i++){
        message += String(buffer4PASS[i]) + ",";
    }
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + message);

    PrintfDebugger::Println("##############Constructor with SSID and PASS############################");

    byte dataOfSSID[32] = {0};
    byte dataOfPASS[32] = {0};

    WiFiSetupCommand command2 = WiFiSetupCommand(dataOfSSID, dataOfPASS);

}
void WiFiSetupCommandTest::Loop()
{

}