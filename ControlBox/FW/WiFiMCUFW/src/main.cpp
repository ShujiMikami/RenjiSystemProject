#include <Arduino.h>
#include "app_LEDToggle.h"
#include "app_WiFiAPScan.h"


const uint32_t MESSAGE_DELAY = 1000;

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


