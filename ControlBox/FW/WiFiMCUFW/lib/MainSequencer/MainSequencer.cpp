#include "WebServerAction.h"
#include "MainSequencer.h"
#include "DebugPrintf.h"
#include "UARTCom.h"
#include "DebugMessageManager.h"
#include "WiFiHTTPServer.h"
#include "WiFiSettingReceivedCommand.h"

//コマンド関係
#include "WiFiSetupCommand.h"

#include <Arduino.h>

const int MainSequencer::MODE_DECISION_PIN = 14;

static WebServerAction::WiFiActionMode_t mode = WebServerAction::WIFI_SETTING_MODE;

void MainSequencer::Setup()
{
    //デバッグメッセージ切り替え
    DebugMessageManager::MessageManage();

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
        PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "Required to change WiFi action mode to " + String(modeSetting));

        mode = WebServerAction::Setup(modeSetting);

        PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "WiFi action mode = " + String(mode));
    }else{
        //ループタスク
        WebServerAction::Loop();
    }

    //イベントのチェック
    int event = WebServerAction::GetEvent();
    if(event != 0){
        PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "event " + String(event) + " occured");
    }

    if(event == 1){
        WiFiSetupCommand command = WiFiSetupCommand(WiFiHTTPServer::GetSSID(), WiFiHTTPServer::GetPASS()); 
        byte byteDataBuf[256];
        int dataLength = command.GetBytes(byteDataBuf, sizeof(byteDataBuf));
        byte receiveBuf[256];
        UARTCom::SendDataAndReceive(byteDataBuf, dataLength, receiveBuf, dataLength, 1000);
    }else if(event == 2){
        WiFiSettingReceivedCommand command = WiFiSettingReceivedCommand();
        byte byteDataBuf[256];
        byte receiveBuf[256];
        int dataLength = command.GetBytes(byteDataBuf, sizeof(byteDataBuf));
        UARTCom::SendDataAndReceive(byteDataBuf, dataLength, receiveBuf, dataLength, 1000);
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
