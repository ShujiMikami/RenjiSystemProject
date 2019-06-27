#ifndef _MAINSEQUENCER_H_
#define _MAINSEQUENCER_H_

#include "WebServerAction.h"

class MainSequencer
{
public:
    static void Setup();
    static void Loop();
    static bool DebugSwitch;
private:
    MainSequencer();
    static WebServerAction::WiFiActionMode_t getModeSettingStatus();
    static void Println(String message);
    static void setupEvents();
private:
    const static int MODE_DECISION_PIN;
};

#endif