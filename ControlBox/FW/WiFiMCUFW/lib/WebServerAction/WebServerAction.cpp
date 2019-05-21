#include "WebServerAction.h"
#include "WiFiHTTPServer.h"
#include "WebServerFormHTML.h"

#define MODE_DECISION_PIN 12

typedef enum{
    WIFI_SETTING_MODE,
    WIFI_RUN_MODE
}WiFiActionMode_t;

static WiFiActionMode_t getWiFiActionMode();

static void callBackPOST_WiFiSet(ESP8266WebServer& server);
static void callBackGET_WiFiSet(ESP8266WebServer& server);

static void callBackPOST_SystemControl(ESP8266WebServer& server);
static void callBackGET_SystemControl(ESP8266WebServer& server);

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
void Setup_WebServer()
{
    if(getWiFiActionMode() == WIFI_SETTING_MODE){
        SetupWiFiServer(callBackGET_WiFiSet, callBackPOST_WiFiSet);
    }else{
        SetupWiFiServer(callBackGET_SystemControl, callBackPOST_SystemControl);
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

