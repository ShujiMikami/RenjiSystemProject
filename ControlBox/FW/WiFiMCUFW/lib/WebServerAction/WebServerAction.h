#ifndef _WEBSERVERACTION_H_
#define _WEBSERVERACTION_H_

#include <Arduino.h>
#include <ESP8266WebServer.h>

class HostInfo_t{
public:
    String GetSSID();
    String GetPass();
private:
    String ssid;
    String pass;
public:
    HostInfo_t(String ssidToSet, String passToSet);
};
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
    static HostInfo_t readHostInfoFromFlash();
    static void writeHostInfoToFile(String ssid, String pass);
private:
    static bool isFileSystemInitialized;
    static const char* settingFileName;
};

#endif