#include "WiFiSetupCommandAction.h"
#include "WiFiSetupCommand.h"
#include "DebugPrintf.h"
#include "WiFiHTTPServer.h"
#include "UARTCom.h"

bool WiFiSetupCommandAction::DebugSwitch = false;

void (*(WiFiSetupCommandAction::GetCallBackPointer)())()
{
    return callBack;
}

void WiFiSetupCommandAction::callBack()
{
    WiFiSetupCommand command = WiFiSetupCommand(WiFiHTTPServer::GetSSID(), WiFiHTTPServer::GetPASS()); 
    WiFiSetupCommand responseCommand = WiFiSetupCommand(UARTCom::SendDataAndReceive(command, 1000));

    if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
        Println(DEBUG_MESSAGE_HEADER + "ACK received");
    }else{
        Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
    }
}
void WiFiSetupCommandAction::Println(String message)
{
    if(DebugSwitch){
        PrintfDebugger::Println(message);
    }
}