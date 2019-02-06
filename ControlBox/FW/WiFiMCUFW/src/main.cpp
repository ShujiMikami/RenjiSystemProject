#include <Arduino.h>
#include <ESP8266WiFi.h>

const uint8_t LED_PIN = 16;
const uint32_t LED_DELAY = 1000;

const uint32_t MESSAGE_DELAY = 1000;

void LEDToggle();
void LEDToggleTask_initialize();
void LEDToggleTask_loop();

void WiFiAPScan();
void WiFiAPScanTask_initialize();
void WiFiAPScanTask_loop();

void SerialTask_initialize();
void SerialTask_loop();

void setup() 
{
  // put your setup code here, to run once:
  LEDToggleTask_initialize();
  SerialTask_initialize();
  WiFiAPScanTask_initialize();
}

void loop()
{
  // put your main code here, to run repeatedly:
  LEDToggleTask_loop();
  SerialTask_loop();
}

void LEDToggle()
{
  static uint8_t value = LOW;

  digitalWrite(LED_PIN, value);

  if(value == LOW){
    value = HIGH;
  }else{
    value = LOW;
  }
}

void LEDToggleTask_initialize()
{
  pinMode(LED_PIN, OUTPUT);
}
void LEDToggleTask_loop()
{
  static uint32_t prevCount = millis();

  uint32_t currentCount = millis();

  if(currentCount - prevCount >= LED_DELAY){
    LEDToggle();
    prevCount = currentCount;
  }
}
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
void SerialTask_initialize()
{
  Serial.begin(115200);
}
void SerialTask_loop()
{
  static uint32_t prevCount = millis();

  uint32_t currentCount = millis();

  if(currentCount - prevCount >= MESSAGE_DELAY){
    Serial.println("Running.");
    prevCount = currentCount;
  }
}


