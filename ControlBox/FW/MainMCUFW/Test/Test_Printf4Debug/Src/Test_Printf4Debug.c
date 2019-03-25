#include "Test_Printf4Debug.h"

#include "stm32f3xx_hal.h"
#include "cmsis_os.h"


#include "Printf4Debug.h"



osThreadId MessageTaskHandle;
void StartMessageTask(const void* argument);

void TestPrintf4Debug()
{
  osThreadDef(MessageTask, StartMessageTask, osPriorityNormal, 0, 128);
  MessageTaskHandle = osThreadCreate(osThread(MessageTask), NULL);
}
void StartMessageTask(const void* argument)
{
  static char msg_buffer[256];
  while(1){

    //タスクの実行状態を取得
    vTaskList(msg_buffer);

    //標準出力に表示
    Printf4Debug(msg_buffer);
    Printf4Debug("\r\n");

    osDelay(1000);
  }
}

