#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include "WiFiHTTPServer.h"

const String pass = "Settings";

ESP8266WebServer server(80);

static void (*callBackFuncGET)(ESP8266WebServer&);
static void (*callBackFuncPOST)(ESP8266WebServer&);

static void handleRootGet();
static void handleRootPost();

void handleRootGET()
{
  callBackFuncGET(server);
}
void handleRootPost()
{
  callBackFuncPOST(server);
}
String GetSSID()
{
  byte mac[WL_MAC_ADDR_LENGTH];
  WiFi.macAddress(mac);
  String ssid = "";
  for (int i = 0; i < WL_MAC_ADDR_LENGTH; i++) {
    ssid += String(mac[i], HEX);
  }

  return ssid;
}
void SetupWiFiServer(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&))
{
  callBackFuncGET = funcForGET;
  callBackFuncPOST = funcForPOST;

  String ssid = GetSSID();

  WiFi.softAP(ssid.c_str(), pass.c_str());

  server.on("/", HTTP_GET, handleRootGet);
  server.on("/", HTTP_POST, handleRootPost);
  server.begin();
}
void LoopForWiFiInterface()
{
  server.handleClient();
}