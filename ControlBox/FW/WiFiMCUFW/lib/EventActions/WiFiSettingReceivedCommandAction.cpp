#include "WiFiSettingReceivedCommandAction.h"
#include "WiFiSettingReceivedCommand.h"
#include "DebugPrintf.h"
#include "UARTCom.h"


void (*(WiFiSettingReceivedCommandAction::GetCallBackPointer)())()
{
    return callBack;
}

void WiFiSettingReceivedCommandAction::callBack()
{
    WiFiSettingReceivedCommand command = WiFiSettingReceivedCommand(); 
    WiFiSettingReceivedCommand responseCommand = WiFiSettingReceivedCommand(UARTCom::SendDataAndReceive(command, 1000));

    if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
        Println(DEBUG_MESSAGE_HEADER + "ACK received");
    }else{
        Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
    }
}
