#include "InternalDataExchanger.h"
#include "Commands.h"
#include "UARTCom.h"
#include "DebugPrintf.h"

bool InternalDataExchanger::DebugSwitch = false;

InternalDataExchanger::Status_t InternalDataExchanger::NotifyWiFiSetupModeLaunched(String SSID, String PASS)
{
    Status_t result = NO_REPLY;
    
    WiFiSetupCommand command = WiFiSetupCommand(SSID, PASS); 
    WiFiSetupCommand responseCommand = WiFiSetupCommand(UARTCom::SendDataAndReceive(command, 1000));
    
    if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
        Println(DEBUG_MESSAGE_HEADER + "ACK received");
        result = ACK_RECEIVED;
    }else{
        Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
        result = NO_REPLY;
    }

    return result;
}
InternalDataExchanger::Status_t InternalDataExchanger::NotifyWiFiSetupReceivedFromHost()
{
    Status_t result = NO_REPLY;
    WiFiSettingReceivedCommand command = WiFiSettingReceivedCommand(); 
    WiFiSettingReceivedCommand responseCommand = WiFiSettingReceivedCommand(UARTCom::SendDataAndReceive(command, 1000));

    if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
        Println(DEBUG_MESSAGE_HEADER + "ACK received");
        result = ACK_RECEIVED;
    }else{
        Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
        result = NO_REPLY;
    }

    return result;
}
InternalDataExchanger::Status_t InternalDataExchanger::NotifyWiFiRouterConnectionResult(bool connectionResult)
{
    return NO_REPLY;
}
InternalDataExchanger::Status_t InternalDataExchanger::GetCageStatus(CageStatus_t& cageStatusBuf)
{
    return NO_REPLY;

}
void InternalDataExchanger::Println(String message)
{
    if(DebugSwitch){
        PrintfDebugger::Println(message);
    }
}