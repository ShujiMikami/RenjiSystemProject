#include <Arduino.h>

#include "app_LEDToggle.h"
#include "TaskMessager.h"


const uint8_t LED_PIN = 16;
const uint32_t LED_DELAY = 1000;

const uint32_t MESSAGE_DELAY = 1000;
const String TASK_NAME = "LEDTask";

static void LEDToggle();
static void LEDToggleRoutine();

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
void LEDToggleRoutine()
{
  static uint32_t prevCount = millis();

  uint32_t currentCount = millis();

  if(currentCount - prevCount >= LED_DELAY){
    LEDToggle();
    prevCount = currentCount;
  }
}

void LEDToggleTask_initialize()
{
  pinMode(LED_PIN, OUTPUT);
  TaskMessagerInitialize();
}
void LEDToggleTask_loop()
{
  LEDToggleRoutine();
  TaskMessage(TASK_NAME, "Running", MESSAGE_DELAY);
}
