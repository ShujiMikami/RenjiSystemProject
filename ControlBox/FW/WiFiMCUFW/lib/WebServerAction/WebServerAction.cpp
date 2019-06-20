#include "WebServerAction.h"
#include "WiFiHTTPServer.h"
#include "WebServerFormHTML.h"
#include "DebugPrintf.h"


WebServerAction::WiFiActionMode_t WebServerAction::Setup(WiFiActionMode_t actionMode)
{
    WiFiActionMode_t result = actionMode;

    if(actionMode == WIFI_SETTING_MODE){
        WiFiHTTPServer::Setup_AP(callBackGET_WiFiSet, callBackPOST_WiFiSet);
    }else{
        String storedSSID = readSSIDFromFlash();
        String storedPass = readPASSFromFlash();
        bool connectionTryResult = WiFiHTTPServer::Setup(callBackGET_SystemControl, callBackPOST_SystemControl, storedSSID, storedPass);
        if(!connectionTryResult){
            WiFiHTTPServer::Setup_AP(callBackGET_WiFiSet, callBackPOST_WiFiSet);
            result = WIFI_SETTING_MODE;
        }
    }

    return result;
}
void WebServerAction::Loop()
{
    WiFiHTTPServer::LoopForWiFiInterface();
}

void WebServerAction::callBackPOST_WiFiSet(ESP8266WebServer& server)
{

}
void WebServerAction::callBackGET_WiFiSet(ESP8266WebServer& server)
{
    server.send(200, "text/html", Form_WiFiSetting);
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "Sent WiFi setting form");
}

void WebServerAction::callBackPOST_SystemControl(ESP8266WebServer& server)
{
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "Received WiFi setting");
}
void WebServerAction::callBackGET_SystemControl(ESP8266WebServer& server)
{
    server.send(200, "text/html", Form_SystemControl);
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "Sent system control form");
}

String WebServerAction::readSSIDFromFlash()
{
    return "SSID";
}
String WebServerAction::readPASSFromFlash()
{
    return "PASS";
}

