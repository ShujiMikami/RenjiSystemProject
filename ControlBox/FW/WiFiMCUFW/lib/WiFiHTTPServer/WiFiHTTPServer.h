#ifndef _WIFIHTTPSERVER_H_
#define _WIFIHTTPSERVER_H_

#include <Arduino.h>
#include <ESP8266WebServer.h>

void SetupWiFiServer(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&), const String& ssid, const String& pass);
void SetupWiFiServer_AccessPoint(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&));
void LoopForWiFiInterface();

String GetSSID();

class WiFiHTTPServer
{
public:
    static void Setup(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&), const String& ssid, const String& pass);
    static void Setup_AP(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&));
    static void LoopForWiFiInterface();
    static String GetSSID();
private:
    WiFiHTTPServer();
    static ESP8266WebServer* pServer;
    static void (*callBackFuncGET)(ESP8266WebServer&);
    static void (*callBackFuncPOST)(ESP8266WebServer&);

    static void handleRootGet();
    static void handleRootPost();
};

#endif