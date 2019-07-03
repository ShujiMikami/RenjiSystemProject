#include "DebugMessageManager.h"

//デバッグスイッチを含むモジュールを追加するたびにここにincludeを追記
#include "WebServerAction.h"
#include "WiFiHTTPServer.h"
#include "UARTCom.h"
#include "Command_t.h"
#include "MainSequencer.h"
#include "EventActions.h"
#include "EventHandler.h"

void DebugMessageManager::MessageManage()
{
    WebServerAction::DebugSwitch = true;
    WiFiHTTPServer::DebugSwitch = false;
    UARTCom::DebugSwitch = false;
    Command_t::DebugSwitch = false;
    MainSequencer::DebugSwitch = true;
    EventHandler::DebugSwitch = true;
    CommandAction::DebugSwitch = true;
}