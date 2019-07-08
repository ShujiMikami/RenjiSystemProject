#include "CageStatusGetCommandAction.h"
#include "CageStatusGetCommand.h"
#include "DebugPrintf.h"
#include "UARTCom.h"
#include "WebServerAction.h"

void (*(CageStatusGetCommandAction::GetCallBackPointer)())()
{
    return callBack;
}

void CageStatusGetCommandAction::callBack()
{
    CageStatusGetCommand command = CageStatusGetCommand(); 
    Println(DEBUG_MESSAGE_HEADER + "receiving response");
    CageStatusGetCommand responseCommand = CageStatusGetCommand(UARTCom::SendDataAndReceive(command, 1000));

    if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){

        Println(DEBUG_MESSAGE_HEADER + "ACK received");
    }else{
        Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
    }
}
