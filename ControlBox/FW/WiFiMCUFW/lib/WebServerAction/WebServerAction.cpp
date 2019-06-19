#include "WebServerAction.h"
#include "WiFiHTTPServer.h"
#include "WebServerFormHTML.h"


void WebServerAction::Setup(WiFiActionMode_t actionMode)
{
    if(actionMode == WIFI_SETTING_MODE){
        WiFiHTTPServer::Setup_AP(callBackGET_WiFiSet, callBackPOST_WiFiSet);
    }else{
        String storedSSID = readSSIDFromFlash();
        String storedPass = readPASSFromFlash();
        WiFiHTTPServer::Setup(callBackGET_SystemControl, callBackPOST_SystemControl, storedSSID, storedPass);
//        WiFiHTTPServer::Setup_AP(callBackGET_WiFiSet, callBackPOST_WiFiSet);
    }
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
    Serial1.println("Sent WiFi setting form");
    server.send(200, "text/html", Form_WiFiSetting);
}

void WebServerAction::callBackPOST_SystemControl(ESP8266WebServer& server)
{
    Serial1.println("Received WiFi setting");
}
void WebServerAction::callBackGET_SystemControl(ESP8266WebServer& server)
{
    Serial1.println("Sent system control form");
    server.send(200, "text/html", Form_SystemControl);
}

String WebServerAction::readSSIDFromFlash()
{
    return "SSID";
}
String WebServerAction::readPASSFromFlash()
{
    return "PASS";
}


/*
#define MODE_DECISION_PIN 14

static WiFiActionMode_t getWiFiActionMode();

static void callBackPOST_WiFiSet(ESP8266WebServer& server);
static void callBackGET_WiFiSet(ESP8266WebServer& server);

static void callBackPOST_SystemControl(ESP8266WebServer& server);
static void callBackGET_SystemControl(ESP8266WebServer& server);

static String readSSIDFromFlash();
static String readPASSFromFlash();

WiFiActionMode_t getWiFiActionMode()
{
    WiFiActionMode_t result = WIFI_RUN_MODE;

    pinMode(MODE_DECISION_PIN, INPUT);

    int decisionPinState = digitalRead(MODE_DECISION_PIN);

    if(decisionPinState == HIGH){
        result = WIFI_SETTING_MODE;
    }
    else
    {
        result = WIFI_RUN_MODE;
    }

    return result;
}
String readSSIDFromFlash()
{

}
String readPASSFromFlash()
{

}

void Setup_WebServer(WiFiActionMode_t actionMode)
{
    if(actionMode == WIFI_SETTING_MODE){
        SetupWiFiServer_AccessPoint(callBackGET_WiFiSet, callBackPOST_WiFiSet);
    }else{
        String storedSSID = readSSIDFromFlash();
        String storedPass = readPASSFromFlash();
        SetupWiFiServer(callBackGET_SystemControl, callBackPOST_SystemControl, storedSSID, storedPass);
    }
}
void Loop_WebServer()
{
    LoopForWiFiInterface();
}
void callBackPOST_WiFiSet(ESP8266WebServer server)
{

}
void callBackGET_WiFiSet(ESP8266WebServer server)
{
    server.send(200, "text/html", Form_WiFiSetting);
}
void callBackPOST_SystemControl(ESP8266WebServer server)
{

}
void callBackGET_SystemControl(ESP8266WebServer server)
{
    server.send(200, "text/html", Form_SystemControl);
}
*/
