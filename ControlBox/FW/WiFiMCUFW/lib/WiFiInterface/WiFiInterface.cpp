#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include "WiFiInterface.h"

const String pass = "Settings";

static const String formHTML = 
"<h1>Wi-Fi Settings</h1>"
"<form method='post'>"
"  <input type='text' name='ssid' placeholder='ssid'><br>"
"  <input type='text' name='pass' placeholder='pass'><br>"
"  <input type='submit'><br>"
"</form>";

ESP8266WebServer server(80);

static void handleRootGet();

void handleRootGet() {
  server.send(200, "text/html", formHTML);
}

void SetupForWiFiSet()
{
  Serial.begin(115200);

  byte mac[WL_MAC_ADDR_LENGTH];
  WiFi.macAddress(mac);
  String ssid = "";
  for (int i = 0; i < WL_MAC_ADDR_LENGTH; i++) {
    ssid += String(mac[i], HEX);
  }
  Serial.println("SSID: " + ssid);
  Serial.println("PASS: " + pass);
 
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid.c_str(), pass.c_str());
 
  server.on("/", HTTP_GET, handleRootGet);
  server.begin();
  Serial.println("HTTP server started.");
}
void LoopForWiFiInterface()
{
  server.handleClient();
}