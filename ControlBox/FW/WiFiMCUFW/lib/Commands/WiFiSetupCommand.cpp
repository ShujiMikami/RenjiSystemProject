#include "WiFiSetupCommand.h"
#include "FormatInfo.h"

#define SSID_START_POS DATA_START_POS
#define SSID_BYTE_SIZE 32
#define PASS_START_POS (SSID_START_POS + SSID_BYTE_SIZE - 1)
#define PASS_BYTE_SIZE 32

#define SUCCESS_RESULT 0
#define ERROR_RESULT -1

WiFiSetupCommand::WiFiSetupCommand(byte* dataArray, size_t arrayLength) : Command_t(dataArray, arrayLength)
{
    if(commandContentsValid){//チェックサムOKの場合は, コマンドコードが正しいかチェックする
        commandContentsValid = (commandCode == CommandCode);
    }
}
int WiFiSetupCommand::GetSSID(byte* buffer, size_t bufferSize)
{
    int result = SUCCESS_RESULT;

    if(bufferSize < SSID_BYTE_SIZE){
        result = ERROR_RESULT;
    }
    else if(commandContentsValid){
        for(int i = 0; i < SSID_BYTE_SIZE; i++){
            buffer[i] = dataBuffer[SSID_START_POS + i];
        }
        result = SUCCESS_RESULT;
    }
    else{
        result = ERROR_RESULT;
    }

    return result;
}
int WiFiSetupCommand::GetPass(byte* buffer, size_t bufferSize)
{
    int result = SUCCESS_RESULT;

    if(bufferSize < PASS_BYTE_SIZE){
        result = ERROR_RESULT;
    }
    else if(commandContentsValid){
        for(int i = 0; i < PASS_BYTE_SIZE; i++){
            buffer[i] = dataBuffer[PASS_START_POS + i];
        }
        result = SUCCESS_RESULT;
    }
    else{
        result = ERROR_RESULT;
    }

    return result;
}
