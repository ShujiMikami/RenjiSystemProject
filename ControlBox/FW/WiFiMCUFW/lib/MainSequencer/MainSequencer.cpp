#include "WebServerAction.h"
#include "MainSequencer.h"
#include "DebugPrintf.h"
#include "UARTCom.h"
#include "WiFiHTTPServer.h"

//コマンド関係
#include "WiFiSetupCommand.h"
#include "WiFiSettingReceivedCommand.h"
#include "WiFiRouterConnectionCommand.h"

#include <Arduino.h>

const int MainSequencer::MODE_DECISION_PIN = 14;

static WebServerAction::WiFiActionMode_t mode = WebServerAction::WIFI_SETTING_MODE;
bool MainSequencer::DebugSwitch = false;

void MainSequencer::Setup()
{
    //UARTの初期設定
    UARTCom::Setup();

    //初期のモード設定
    WebServerAction::Setup(mode);
}
void MainSequencer::Loop()
{
    //スイッチ状態により, 動作切り替え
    WebServerAction::WiFiActionMode_t modeSetting = getModeSettingStatus();

    if(mode != modeSetting){
        Println(DEBUG_MESSAGE_HEADER + "Required to change WiFi action mode to " + String(modeSetting));

        mode = WebServerAction::Setup(modeSetting);

        Println(DEBUG_MESSAGE_HEADER + "WiFi action mode = " + String(mode));
    }else{
        //ループタスク
        WebServerAction::Loop();
    }

    //イベントのチェック
    int event = WebServerAction::GetEvent();
    if(event != 0){
        Println(DEBUG_MESSAGE_HEADER + "event " + String(event) + " occured");
    }

    if(event == 1){
        WiFiSetupCommand command = WiFiSetupCommand(WiFiHTTPServer::GetSSID(), WiFiHTTPServer::GetPASS()); 
        WiFiSetupCommand responseCommand = WiFiSetupCommand(UARTCom::SendDataAndReceive(command, 1000));

        if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
            Println(DEBUG_MESSAGE_HEADER + "ACK received");
        }else{
            Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
        }
    }else if(event == 2){
        WiFiSettingReceivedCommand command = WiFiSettingReceivedCommand();
        WiFiSettingReceivedCommand responseCommand = WiFiSettingReceivedCommand(UARTCom::SendDataAndReceive(command, 1000));

        if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
            Println(DEBUG_MESSAGE_HEADER + "ACK received");
        }else{
            Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
        }
    }else if(event == 3){
        WiFiRouterConnectionCommand command = WiFiRouterConnectionCommand((byte)mode);
        WiFiRouterConnectionCommand responseCommand = WiFiRouterConnectionCommand(UARTCom::SendDataAndReceive(command, 1000));

        if(responseCommand.IsValidCommand() && responseCommand.GetResponse() == 0){
            Println(DEBUG_MESSAGE_HEADER + "ACK received");
        }else{
            Println(DEBUG_MESSAGE_HEADER + "trouble in UART COM");
        }
    }

}

void MainSequencer::Println(String message)
{
    if(DebugSwitch){
        PrintfDebugger::Println(message);
    }
}
WebServerAction::WiFiActionMode_t MainSequencer::getModeSettingStatus()
{
    WebServerAction::WiFiActionMode_t result = WebServerAction::WIFI_RUN_MODE;

    pinMode(MODE_DECISION_PIN, INPUT);

    int decisionPinState = digitalRead(MODE_DECISION_PIN);

    if(decisionPinState == HIGH){
        result = WebServerAction::WIFI_SETTING_MODE;
    }
    else
    {
        result = WebServerAction::WIFI_RUN_MODE;
    }

    return result;
}
