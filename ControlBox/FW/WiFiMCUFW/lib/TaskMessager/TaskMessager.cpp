#include <Arduino.h>
#include "TaskMessager.h"

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
