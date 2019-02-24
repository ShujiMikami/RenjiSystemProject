#include <Arduino.h>
#include "TaskMessager.h"
/*
static bool isInitialied = false;
static int SERIAL_SPEED = 115200;

static bool usingFlag = false;

void TaskMessagerInitialize()
{
    if(!isInitialied){
        Serial.begin(SERIAL_SPEED);
        isInitialied = true;
    }
}

void TaskMessage(String taskName, String msg, int delayTime)
{
    static uint32_t prevCount = millis();

    uint32_t currentCount = millis();

    if((currentCount - prevCount >= delayTime) && !usingFlag){
        usingFlag = true;

        Serial.println("[" + taskName + "]" + msg);
        prevCount = currentCount;

        usingFlag = false;
    }
}
*/
bool TaskMessager::isInitialized = false;

TaskMessager::TaskMessager(String task_Name, String msg, int period_ms)
{
    taskName = task_Name;
    message = msg;
    period = period_ms;

    prevCount = millis();

    if(!isInitialized){
        Serial.begin(SERIAL_BAUD);
        isInitialized = true;
    }
}
void TaskMessager::routine()
{
    uint32_t currentCount = millis();

    if(currentCount - prevCount >= period){

        Serial.println("[" + taskName + "]" + message);
        prevCount = currentCount;
    }
}
TaskMessager::~TaskMessager()
{
}
