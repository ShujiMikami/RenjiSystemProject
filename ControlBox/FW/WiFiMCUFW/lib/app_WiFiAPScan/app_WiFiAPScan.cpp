#include <Arduino.h>
#include <ESP8266WiFi.h>

static void WiFiAPScan();

void WiFiAPScan()
{
  WiFi.scanNetworks(true, false, 0, NULL);
}
void WiFiAPScanTask_initialize()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
}
void WiFiAPScanTask_loop()
{

}
