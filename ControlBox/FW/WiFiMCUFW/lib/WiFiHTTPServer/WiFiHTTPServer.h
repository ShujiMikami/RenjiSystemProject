#ifndef _WIFIHTTPSERVER_H_
#define _WIFIHTTPSERVER_H_

#include <Arduino.h>
#include <ESP8266WebServer.h>

void SetupWiFiServer(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&));
void LoopForWiFiInterface();

String GetSSID();

#endif