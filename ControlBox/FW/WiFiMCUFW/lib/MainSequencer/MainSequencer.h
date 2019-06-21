#ifndef _MAINSEQUENCER_H_
#define _MAINSEQUENCER_H_

#include "WebServerAction.h"

class MainSequencer
{
public:
    static void Setup();
    static void Loop();
private:
    MainSequencer();
    static WebServerAction::WiFiActionMode_t getModeSettingStatus();
private:
    const static int MODE_DECISION_PIN;
};



#endif