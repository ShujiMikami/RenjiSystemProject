#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

const String pass = "Settings";

ESP8266WebServer server(80);

static void handleRootGet();

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);


  byte mac[6];
  WiFi.macAddress(mac);
  String ssid = "";
  for (int i = 0; i < 6; i++) {
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

void loop()
{
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void handleRootGet() {
  String html = "";
  html += "<h1>Wi-Fi Settings</h1>";
  html += "<form method='post'>";
  html += "  <input type='text' name='ssid' placeholder='ssid'><br>";
  html += "  <input type='text' name='pass' placeholder='pass'><br>";
  html += "  <input type='submit'><br>";
  html += "</form>";
  server.send(200, "text/html", html);
}