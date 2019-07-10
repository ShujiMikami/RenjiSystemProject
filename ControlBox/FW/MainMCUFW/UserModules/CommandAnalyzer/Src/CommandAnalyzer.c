#include "CommandAnalyzer.h"
#include "cmsis_os.h"
#include "APP_UART.h"
#include "Printf4Debug.h"


typedef void (*CallBackPtr_t)(uint8_t*, uint8_t*, uint16_t);


#define COMMAND_BYTE_SIZE 67

static void commandAnalyzeTask();
static int checksumValidation(uint8_t* data, uint16_t dataLength);
static int searchIndexOfCommandCode(uint8_t commandCode);

//コマンドごとのアクション
static void reaction_WiFiSetupModeNotified(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize);
static void reaction_WiFiSettingReceivedNotified(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize);
static void reaction_WiFiRouterConnectionResultNotified(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize);
static void reaction_GetCageStatus(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize);
static void reaction_SetActivationMode(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize);
static void reaction_SetSwitchStatus(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize);
static void reaction_SetTemperatureTable(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize);
static void reaction_SetUVTable(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize);
static void reaction_NotDefinedCommand(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize);


//上のenumの通りに並んでいる前提
const uint8_t commandCodes[] = {
    0x01,
    0x02,
    0x03, 
    0x04,
    0x05,
    0x06,
    0x07, 
    0x08,
    0xFF //NOT_DEFINED用
};

const CallBackPtr_t callBacks[] = {
    reaction_WiFiSetupModeNotified,
    reaction_WiFiSettingReceivedNotified,
    reaction_WiFiRouterConnectionResultNotified,
    reaction_GetCageStatus,
    reaction_SetActivationMode,
    reaction_SetSwitchStatus,
    reaction_SetTemperatureTable,
    reaction_SetUVTable,
    reaction_NotDefinedCommand
}; 

void CommandAnalyzer_Init()
{
    osThreadId commandAnalyzerTaskID;

    osThreadDef(CommandAnalyzeTask, commandAnalyzeTask, osPriorityNormal, 0, 128);
    commandAnalyzerTaskID = osThreadCreate(osThread(CommandAnalyzeTask), NULL);

}
void commandAnalyzeTask()
{
    //UARTスレッドがちゃんと走るの待ち
    while(GetStatus_APP_UART() != APP_UART_RUNNING);

    int isReceiveStarted = 0;

    int timeoutCnt = 0;

    static uint8_t buffer[COMMAND_BYTE_SIZE];
    static uint8_t responseBuffer[COMMAND_BYTE_SIZE];

    while(1){
        if(timeoutCnt > 100){
            FlushBuffer();
            timeoutCnt = 0;
            isReceiveStarted = 0;
        }

        int receivedByteCount = GetRxQueueCount();

        if(isReceiveStarted == 0 && receivedByteCount > 0){
            isReceiveStarted = 1;
        }
        

        if(receivedByteCount >= COMMAND_BYTE_SIZE){
            UARTGetReceivedData(buffer, sizeof(buffer));
            
            if(checksumValidation(buffer, sizeof(buffer)) == 1){
                int callBackIndex = searchIndexOfCommandCode(buffer[0]);
                callBacks[callBackIndex](buffer, responseBuffer, sizeof(responseBuffer));
            }else{
                int cnt = 0;
                for(cnt = 0; cnt < sizeof(responseBuffer); cnt++){
                   responseBuffer[cnt] = buffer[cnt]; 
                }
                responseBuffer[1] = 1;
            }

            UARTSendData(responseBuffer, sizeof(responseBuffer));
            Printf4Debug("%d bytes received\r\n", receivedByteCount);
        }

        if(isReceiveStarted == 1){
            timeoutCnt++;
        }

        osDelay(10);
      }
}
int checksumValidation(uint8_t* data, uint16_t dataLength)
{
    int result = 0;

    if(dataLength >= COMMAND_BYTE_SIZE){
        uint16_t chksum = 0;

        int cnt = 0;
        for(cnt = 0; cnt < COMMAND_BYTE_SIZE - 1; cnt++){
            chksum += (uint16_t)data[cnt];
        }

        result = ((uint8_t)chksum == data[COMMAND_BYTE_SIZE - 1]);
    }

    return result;
}
void reaction_WiFiSetupModeNotified(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize)
{
    //SSID取得
    //PASS取得
    //LCDに表示
    //オウム返し
    int cnt = 0;
    for(cnt = 0; cnt < responseBufferSize; cnt++){
        responseBuffer[cnt] = command[cnt];
    }
}
void reaction_WiFiSettingReceivedNotified(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize)
{
    //特にやることなし
    //オウム返し
    int cnt = 0;
    for(cnt = 0; cnt < responseBufferSize; cnt++){
        responseBuffer[cnt] = command[cnt];
    }
}
void reaction_WiFiRouterConnectionResultNotified(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize)
{
    //LEDに反映
     //オウム返し
    int cnt = 0;
    for(cnt = 0; cnt < responseBufferSize; cnt++){
        responseBuffer[cnt] = command[cnt];
    }
}
void reaction_GetCageStatus(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize)
{
     //オウム返し
    int cnt = 0;
    for(cnt = 0; cnt < responseBufferSize; cnt++){
        responseBuffer[cnt] = command[cnt];
    }

}
void reaction_SetActivationMode(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize)
{
     //オウム返し
    int cnt = 0;
    for(cnt = 0; cnt < responseBufferSize; cnt++){
        responseBuffer[cnt] = command[cnt];
    }

}
void reaction_SetSwitchStatus(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize)
{
     //オウム返し
    int cnt = 0;
    for(cnt = 0; cnt < responseBufferSize; cnt++){
        responseBuffer[cnt] = command[cnt];
    }

}
void reaction_SetTemperatureTable(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize)
{
     //オウム返し
    int cnt = 0;
    for(cnt = 0; cnt < responseBufferSize; cnt++){
        responseBuffer[cnt] = command[cnt];
    }

}
void reaction_SetUVTable(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize)
{
     //オウム返し
    int cnt = 0;
    for(cnt = 0; cnt < responseBufferSize; cnt++){
        responseBuffer[cnt] = command[cnt];
    }

}
void reaction_NotDefinedCommand(uint8_t* command, uint8_t* responseBuffer, uint16_t responseBufferSize)
{
     //オウム返し
    int cnt = 0;
    for(cnt = 0; cnt < responseBufferSize; cnt++){
        responseBuffer[cnt] = command[cnt];
    }

}
int searchIndexOfCommandCode(uint8_t commandCode)
{
    int result = 0xFF;

    int cnt = 0;
    for(cnt = 0; cnt < sizeof(commandCodes); cnt++){
        if(commandCode == commandCodes[cnt]){
            result = cnt;
        }
    }

    return result;
    
}