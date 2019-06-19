#include "WebServerAction.h"
#include "MainSequencer.h"

#include <Arduino.h>

const int MainSequencer::MODE_DECISION_PIN = 14;

static WebServerAction::WiFiActionMode_t mode = WebServerAction::WIFI_SETTING_MODE;

void MainSequencer::Setup()
{
    Serial1.begin(115200);

    //初期のモード設定
    WebServerAction::Setup(mode);
}
void MainSequencer::Loop()
{
    //スイッチ状態により, 動作切り替え
    WebServerAction::WiFiActionMode_t modeSetting = getModeSettingStatus();

    if(mode != modeSetting){
        WebServerAction::Setup(modeSetting);
        mode = modeSetting;

        if(mode == WebServerAction::WIFI_SETTING_MODE){
            Serial1.println("Changed to setting mode");
        }
        else{
            Serial1.println("Changed to run mode");
        }
        
        
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
