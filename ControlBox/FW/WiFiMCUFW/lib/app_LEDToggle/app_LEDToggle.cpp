#include <Arduino.h>

#include "app_LEDToggle.h"

const uint8_t LED_PIN = 16;
const uint32_t LED_DELAY = 1000;

static void LEDToggle();

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
