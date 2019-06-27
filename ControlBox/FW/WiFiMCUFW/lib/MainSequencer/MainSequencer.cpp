#include "WebServerAction.h"
#include "MainSequencer.h"
#include "DebugPrintf.h"
#include "UARTCom.h"

#include "Commands.h"
#include "EventActions.h"
#include "EventHandler.h"

#include <Arduino.h>

const int MainSequencer::MODE_DECISION_PIN = 14;

static WebServerAction::WiFiActionMode_t mode = WebServerAction::WIFI_SETTING_MODE;
bool MainSequencer::DebugSwitch = false;

void MainSequencer::Setup()
{
    //イベントセットアップ
    setupEvents();

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

    EventHandler::ExecuteEvent(event);
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
void MainSequencer::setupEvents()
{
    //初期化
    EventHandler::Setup();

    //イベント登録
    EventHandler::RegisterEvent(WiFiSetupCommand::CommandCode, WiFiSetupCommandAction::GetCallBackPointer());
    EventHandler::RegisterEvent(WiFiSettingReceivedCommand::CommandCode, WiFiSettingReceivedCommandAction::GetCallBackPointer());
    EventHandler::RegisterEvent(WiFiRouterConnectionCommand::CommandCode, WiFiRouterConnectionCommandAction::GetCallBackPointer());
    EventHandler::RegisterEvent(CageStatusGetCommand::CommandCode, CageStatusGetCommandAction::GetCallBackPointer());

}