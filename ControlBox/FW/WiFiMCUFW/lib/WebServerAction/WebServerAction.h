#ifndef _WEBSERVERACTION_H_
#define _WEBSERVERACTION_H_

#include <Arduino.h>
#include <ESP8266WebServer.h>

/* 
typedef enum{
    WIFI_SETTING_MODE,
    WIFI_RUN_MODE
}WiFiActionMode_t;


void Setup_WebServer(WiFiActionMode_t actionMode);
void Loop_WebServer();
*/
class WebServerAction
{
public:
    typedef enum{
        WIFI_SETTING_MODE,
        WIFI_RUN_MODE
    }WiFiActionMode_t;
public:
    static WiFiActionMode_t Setup(WiFiActionMode_t actionMode);
    static void Loop();
private:
    static WiFiActionMode_t getWiFiActionMode();

    static void callBackPOST_WiFiSet(ESP8266WebServer& server);
    static void callBackGET_WiFiSet(ESP8266WebServer& server);

    static void callBackPOST_SystemControl(ESP8266WebServer& server);
    static void callBackGET_SystemControl(ESP8266WebServer& server);

    static String readSSIDFromFlash();
    static String readPASSFromFlash();

};

#endif