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
    Status_t result = NO_REPLY;

    WiFiRouterConnectionCommand command = WiFiRouterConnectionCommand((byte)connectionResult); 
    WiFiRouterConnectionCommand responseCommand = WiFiRouterConnectionCommand(UARTCom::SendDataAndReceive(command, 1000));

    if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
        result = ACK_RECEIVED;
        Println(DEBUG_MESSAGE_HEADER + "ACK received");
    }else{
        result = NO_REPLY;
        Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
    }


    return result;
}
InternalDataExchanger::Status_t InternalDataExchanger::GetCageStatus(CageStatus_t& cageStatusBuf)
{
    Status_t result = NO_REPLY;

    CageStatusGetCommand command = CageStatusGetCommand(); 
    Println(DEBUG_MESSAGE_HEADER + "receiving response");
    CageStatusGetCommand responseCommand = CageStatusGetCommand(UARTCom::SendDataAndReceive(command, 1000));

    if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
        cageStatusBuf = CageStatus_t(responseCommand.GetActivationMode(), responseCommand.GetCurrentTemperature(), responseCommand.GetEnvironmentJudgement(), responseCommand.GetSwitchStatus());
        result = ACK_RECEIVED;
        Println(DEBUG_MESSAGE_HEADER + "ACK received");
    }else{
        result = NO_REPLY;
        Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
    }
    return result;
}
void InternalDataExchanger::Println(String message)
{
    if(DebugSwitch){
        PrintfDebugger::Println(message);
    }
}