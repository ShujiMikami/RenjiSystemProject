#include <Arduino.h>
#include "TaskMessager.h"
#include "app_LEDToggle.h"
#include "app_WiFiAPScan.h"
#include "app_SPIMaster.h"

const uint32_t MESSAGE_DELAY = 1000;
const String TASK_NAME = "MainTask";

static uint8_t dataBuffer[500];

static void setup_Communication();
static void loop_Communication();

void setup() 
{
  // put your setup code here, to run once:
  setup_Communication();
}

void loop()
{
  // put your main code here, to run repeatedly:
  loop_Communication();
  

}

void setup_Communication()
{
  Serial.begin(115200);
}
void loop_Communication()
{

}
