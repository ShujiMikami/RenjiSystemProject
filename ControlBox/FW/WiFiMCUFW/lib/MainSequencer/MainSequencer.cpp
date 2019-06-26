#include "WebServerAction.h"
#include "MainSequencer.h"
#include "DebugPrintf.h"
#include "UARTCom.h"
#include "DebugMessageManager.h"

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
    }
    //ループタスク
    WebServerAction::Loop();
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
