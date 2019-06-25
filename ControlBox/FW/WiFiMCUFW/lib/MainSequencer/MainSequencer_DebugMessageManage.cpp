#include "MainSequencer.h"

//デバッグスイッチを含むモジュールを追加するたびにここにincludeを追記
#include "WebServerAction.h"
#include "WiFiHTTPServer.h"
#include "UARTCom.h"
#include "Command_t.h"


void MainSequencer::debugMessageManage()
{
    WebServerAction::DebugSwitch = true;
    WiFiHTTPServer::DebugSwitch = true;
    UARTCom::DebugSwitch = true;
    Command_t::DebugSwitch = true;
}