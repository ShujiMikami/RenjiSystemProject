#include <Arduino.h>
#include "TaskMessager.h"
#include "app_LEDToggle.h"
#include "app_WiFiAPScan.h"
#include "app_SPIMaster.h"

const uint32_t MESSAGE_DELAY = 1000;
const String TASK_NAME = "MainTask";

void setup() 
{
  // put your setup code here, to run once:
  TaskMessagerInitialize();
  
  LEDToggleTask_initialize();
  SPIMasterTask_initialize();
}

void loop()
{
  // put your main code here, to run repeatedly:
  TaskMessage(TASK_NAME, "Running", MESSAGE_DELAY);

  LEDToggleTask_loop();
  //SPIMasterTask_loop();
}

