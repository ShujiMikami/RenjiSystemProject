#include <Arduino.h>
#include "app_LEDToggle.h"
#include "app_WiFiAPScan.h"
#include "app_SPIMaster.h"

const uint32_t MESSAGE_DELAY = 1000;
const String TASK_NAME = "MainTask";

void MainTask_initialize();
void MainTask_loop();

void setup() 
{
  // put your setup code here, to run once:
  LEDToggleTask_initialize();
  MainTask_initialize();
  SPIMasterTask_initialize();
}

void loop()
{
  // put your main code here, to run repeatedly:
  LEDToggleTask_loop();
  MainTask_loop();
  SPIMasterTask_loop();
}

void MainTask_initialize()
{
  Serial.begin(115200);
}
void MainTask_loop()
{
  static uint32_t prevCount = millis();

  uint32_t currentCount = millis();

  if(currentCount - prevCount >= MESSAGE_DELAY){
    Serial.println("[" + TASK_NAME + "]" + "Running");
    prevCount = currentCount;
  }
}


