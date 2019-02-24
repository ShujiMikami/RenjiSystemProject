#ifndef _TASKMESSAGER_H_
#define _TASKMESSAGER_H_

#include <Arduino.h>

/*
void TaskMessagerInitialize();
void TaskMessage(String taskName, String msg, int delayTime);
*/

class TaskMessager
{
private:
    /* data */
    uint32_t prevCount;
    static bool isInitialized;
    String taskName;
    String message;
    uint32_t period;
    static const uint32_t SERIAL_BAUD = 115200;
public:
    TaskMessager(String task_Name, String msg, int period_ms);
    ~TaskMessager();
    void routine();
};


#endif