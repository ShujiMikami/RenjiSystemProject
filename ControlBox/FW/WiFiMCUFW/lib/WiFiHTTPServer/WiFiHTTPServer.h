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
    void Setup(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&), const String& ssid, const String& pass);
    void Setup_AP(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&));
    void LoopForWiFiInterface();
    String GetSSID();


};

#endif