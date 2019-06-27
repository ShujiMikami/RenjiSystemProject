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
        WIFI_RUN_MODE,
        WIFI_STOP_MODE
    }WiFiActionMode_t;
public:
    static WiFiActionMode_t Setup(WiFiActionMode_t actionMode);
    static void Loop();
    static bool DebugSwitch;
    static int GetEvent();
    static int PeekEvent();
private:
    static WiFiActionMode_t getWiFiActionMode();
    static void callBackPOST_WiFiSet(ESP8266WebServer& server);
    static void callBackGET_WiFiSet(ESP8266WebServer& server);
    static void callBackPOST_SystemControl(ESP8266WebServer& server);
    static void callBackGET_SystemControl(ESP8266WebServer& server);
    static HostInfo_t readHostInfoFromFlash();
    static void writeHostInfoToFile(String ssid, String pass);
    static void Println(String message);
private:
    static bool isFileSystemInitialized;
    static const char* settingFileName;
    static int event;
};

#endif