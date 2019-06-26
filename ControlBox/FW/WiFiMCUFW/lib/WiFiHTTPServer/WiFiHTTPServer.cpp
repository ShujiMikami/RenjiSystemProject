#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include "WiFiHTTPServer.h"
#include <ESP8266mDNS.h>
#include "DebugPrintf.h"

ESP8266WebServer WiFiHTTPServer::server(80); 

static void (*callBackFuncGET)(ESP8266WebServer&);
static void (*callBackFuncPOST)(ESP8266WebServer&);

const static int CONNECTION_DELAY_LIMIT = 100;

const String WiFiHTTPServer::pass = "settings";

bool WiFiHTTPServer::DebugSwitch = false;

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
String WiFiHTTPServer::GetPASS()
{
  return pass;
}
bool WiFiHTTPServer::Setup(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&), const String& ssid, const String& pass)
{
  bool result = true;

  server.close();

  callBackFuncGET = funcForGET;
  callBackFuncPOST = funcForPOST;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Println(DEBUG_MESSAGE_HEADER + "Trying to connect to SSID : " + ssid + " with PASS : " + pass);
  
  Printf(DEBUG_MESSAGE_HEADER + "waiting for connection");
  while(WiFi.status() != WL_CONNECTED){
    static int cnt = 0;

    Printf(".");
    delay(100);

    if(cnt++ > CONNECTION_DELAY_LIMIT){
      result = false;
      cnt = 0;

      Println("connection timeout");
      break;
    }
    else{
      wdt_reset();
    }
  }

  if(result){
    if(MDNS.begin("RenjiSystemServer")){
      Println(DEBUG_MESSAGE_HEADER + "mDNS started");
    }

    server.on("/", HTTP_GET, handleRootGET);
    server.on("/", HTTP_POST, handleRootPOST);
    server.begin();
  }

  return result;
}
void WiFiHTTPServer::Setup_AP(void (*funcForGET)(ESP8266WebServer&), void (*funcForPOST)(ESP8266WebServer&))
{
  server.close();

  callBackFuncGET = funcForGET;
  callBackFuncPOST = funcForPOST;

  String ssid = GetSSID();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid.c_str(), pass.c_str());

  delay(100);

  server.on("/", HTTP_GET, handleRootGET);
  server.on("/", HTTP_POST, handleRootPOST);
  server.begin();

  Println(DEBUG_MESSAGE_HEADER + "WiFi setting server started. SSID = " + ssid + ", PASS = " + pass);
}
void WiFiHTTPServer::LoopForWiFiInterface()
{
  server.handleClient();
}
void WiFiHTTPServer::Println(String message)
{
  if(DebugSwitch){
    PrintfDebugger::Println(message);
  }
}
void WiFiHTTPServer::Printf(String message)
{
  if(DebugSwitch){
    PrintfDebugger::Printf(message);
  }
}
void WiFiHTTPServer::WiFi_Stop()
{
  server.close();
  WiFi.mode(WIFI_OFF);
}