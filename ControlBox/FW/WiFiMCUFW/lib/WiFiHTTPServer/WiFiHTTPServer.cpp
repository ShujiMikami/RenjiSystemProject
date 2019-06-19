#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include "WiFiHTTPServer.h"
#include <ESP8266mDNS.h>

ESP8266WebServer WiFiHTTPServer::server(80); 

static void (*callBackFuncGET)(ESP8266WebServer&);
static void (*callBackFuncPOST)(ESP8266WebServer&);

const static int CONNECTION_DELAY_LIMIT = 100;

const String WiFiHTTPServer::pass = "settings";

void WiFiHTTPServer::handleRootPOST()
{
  callBackFuncPOST(server);
}
void WiFiHTTPServer::handleRootGET()
{
  callBackFuncGET(server);
}
String WiFiHTTPServer::GetSSID()
{
  byte mac[WL_MAC_ADDR_LENGTH];
  WiFi.macAddress(mac);
  String ssid = "";
  for (int i = 0; i < WL_MAC_ADDR_LENGTH; i++) {
    ssid += String(mac[i], HEX);
  }

  return ssid;
}
void WiFiHTTPServer::Setup(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&), const String& ssid, const String& pass)
{
  server.close();

  callBackFuncGET = funcForGET;
  callBackFuncPOST = funcForPOST;

  WiFi.disconnect();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  while(WiFi.status() != WL_CONNECTED){
    static int cnt = 0;

    Serial1.printf("waiting for connection\r\n");
    delay(100);

    if(cnt++ > CONNECTION_DELAY_LIMIT){
      Serial1.println("connection timeout");
      break;
    }
    else{
      wdt_reset();
    }
  }

  if(MDNS.begin("RenjiSystemServer")){
    Serial1.printf("mDNS started\r\n");
  }

  server.on("/", HTTP_GET, handleRootGET);
  server.on("/", HTTP_POST, handleRootPOST);
  server.begin();

}
void WiFiHTTPServer::Setup_AP(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&))
{
  server.close();

  callBackFuncGET = funcForGET;
  callBackFuncPOST = funcForPOST;

  String ssid = GetSSID();

  WiFi.softAP(ssid.c_str(), pass.c_str());

  server.on("/", HTTP_GET, handleRootGET);
  server.on("/", HTTP_POST, handleRootPOST);
  server.begin();

}
void WiFiHTTPServer::LoopForWiFiInterface()
{
  server.handleClient();
}

/*
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
void SetupWiFiServer(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&), const String& ssid, const String& pass)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED){
  }

  if(MDNS.begin("RenjiSystemServer")){

  }

  server.on("/", HTTP_GET, handleRootGet);
  server.on("/", HTTP_POST, handleRootPost);
  server.begin();
}
void SetupWiFiServer_AccessPoint(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&))
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
*/