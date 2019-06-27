#include "WiFiRouterConnectionCommandAction.h"
#include "WiFiRouterConnectionCommand.h"
#include "DebugPrintf.h"
#include "UARTCom.h"
#include "WebServerAction.h"

void (*(WiFiRouterConnectionCommandAction::GetCallBackPointer)())()
{
    return callBack;
}

void WiFiRouterConnectionCommandAction::callBack()
{
    WiFiRouterConnectionCommand command = WiFiRouterConnectionCommand(WebServerAction::GetEventArg()); 
    WiFiRouterConnectionCommand responseCommand = WiFiRouterConnectionCommand(UARTCom::SendDataAndReceive(command, 1000));

    if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
        Println(DEBUG_MESSAGE_HEADER + "ACK received");
    }else{
        Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
    }
}
