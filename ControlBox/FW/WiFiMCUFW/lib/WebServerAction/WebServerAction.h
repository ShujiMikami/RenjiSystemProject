#ifndef _WEBSERVERACTION_H_
#define _WEBSERVERACTION_H_

typedef enum{
    WIFI_SETTING_MODE,
    WIFI_RUN_MODE
}WiFiActionMode_t;


void Setup_WebServer(WiFiActionMode_t actionMode);
void Loop_WebServer();

class WebServerAction
{
    typedef enum{
        WIFI_SETTING_MODE,
        WIFI_RUN_MODE
    }WiFiActionMode_t;
public:
    static void setup(WiFiActionMode_t actionMode);
    static void loop();
private:
    static WiFiActionMode_t getWiFiActionMode();

    static void callBackPOST_WiFiSet(ESP8266WebServer& server);
    static void callBackGET_WiFiSet(ESP8266WebServer& server);

    static void callBackPOST_SystemControl(ESP8266WebServer& server);
    static void callBackGET_SystemControl(ESP8266WebServer& server);

    static String readSSIDFromFlash();
    static String readPASSFromFlash();

    const static int MODE_DECISION_PIN;
};

#endif