#include <Arduino.h>

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