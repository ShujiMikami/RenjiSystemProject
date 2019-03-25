#ifndef _PRINTF4DEBUG_H_
#define _PRINTF4DEBUG_H_
#endif
typedef enum{
    Printf4Debug_STANDBY,
    Printf4Debug_RUNNING,
    Printf4Debug_ERROR_STOPPED
}Printf4Debug_Stauts_t;

void Printf4Debug(const char* format, ...);
void PrintfInit();
Printf4Debug_Stauts_t GetStatus_Printf4Debug();
