#include "WiFiSetupCommandAction.h"
#include "WiFiSetupCommand.h"
#include "DebugPrintf.h"
#include "UARTCom.h"
#include "WebServerAction.h"

void (*(WiFiSetupCommandAction::GetCallBackPointer)())()
{
    return callBack;
}

void WiFiSetupCommandAction::callBack()
{
    WiFiSetupCommand command = WiFiSetupCommand(WebServerAction::GetEventArg()); 
    Println(DEBUG_MESSAGE_HEADER + "receiving response");
    WiFiSetupCommand responseCommand = WiFiSetupCommand(UARTCom::SendDataAndReceive(command, 1000));

    if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
        Println(DEBUG_MESSAGE_HEADER + "ACK received");
    }else{
        Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
    }
}
