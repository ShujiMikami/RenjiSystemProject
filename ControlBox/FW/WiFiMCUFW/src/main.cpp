#include <Arduino.h>
#include "TaskMessager.h"
#include "app_LEDToggle.h"
#include "app_WiFiAPScan.h"
#include "app_SPIMaster.h"

const uint32_t MESSAGE_DELAY = 1000;
const String TASK_NAME = "MainTask";

TaskMessager messager(TASK_NAME, "Running.", MESSAGE_DELAY);

const uint8_t SLAVE_SELECT_PIN = 5;

void setup() 
{
  // put your setup code here, to run once:
  LEDToggleTask_initialize();
  //SPIMasterTask_initialize();
  SPIMaster_initialize(SLAVE_SELECT_PIN, SPISettings(100000, MSBFIRST, SPI_MODE0));
}

void loop()
{
  // put your main code here, to run repeatedly:
  messager.routine();
  

  LEDToggleTask_loop();
  //SPIMasterTask_loop();
}

