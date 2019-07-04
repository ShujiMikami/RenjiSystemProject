#ifndef _WIFIHTTPSERVER_H_
#define _WIFIHTTPSERVER_H_

#include <Arduino.h>
#include <ESP8266WebServer.h>

class WiFiHTTPServer
{
public:
    static bool Setup(String* requests, int numOfRequests, void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&), const String& ssid, const String& pass);
    static void Setup_AP(String* requests, int numOfRequests, void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&));
    static void WiFi_Stop();
    static void LoopForWiFiInterface();
    static String GetSSID();
    static String GetPASS();
    static bool DebugSwitch;
private:
    static ESP8266WebServer server;
    static const String pass;
private:
    WiFiHTTPServer();
    static void handleRootGET();
    static void handleRootPOST();
    static void Println(String message);
    static void Printf(String message);
};

#endif