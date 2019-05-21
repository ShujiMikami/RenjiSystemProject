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

void Setup_WebServer()
{
    if(getWiFiActionMode() == WIFI_SETTING_MODE){
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

