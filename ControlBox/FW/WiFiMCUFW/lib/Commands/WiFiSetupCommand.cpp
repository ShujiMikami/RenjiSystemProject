#include "WiFiSetupCommand.h"
#include "FormatInfo.h"
#include "DebugPrintf.h"

const int SSID_START_POS = DATA_START_POS;
const int SSID_BYTE_SIZE = 32;
const int PASS_START_POS = SSID_START_POS + SSID_BYTE_SIZE;
const int PASS_BYTE_SIZE = 32;

const int SUCCESS_RESULT = 0;
const int ERROR_RESULT = -1;

WiFiSetupCommand::WiFiSetupCommand(byte* dataArray, size_t arrayLength) : Command_t(dataArray, arrayLength)
{
    if(commandContentsValid){//チェックサムOKの場合は, コマンドコードが正しいかチェックする
        Println(DEBUG_MESSAGE_HEADER + "checkSum is OK");
        commandContentsValid = (commandCode == CommandCode);
        Println(DEBUG_MESSAGE_HEADER + "Command Validation result = " + String(commandContentsValid));
    }
}
WiFiSetupCommand::WiFiSetupCommand(byte* SSID, byte* PASS)
{
    dataBuffer[COMMAND_CODE_POS] = CommandCode;

    for(int i = 0; i < SSID_BYTE_SIZE; i++){
        dataBuffer[SSID_START_POS + i] = SSID[i];
        Println(DEBUG_MESSAGE_HEADER + "copied " + String(SSID[i]) + " to " + String(SSID_START_POS + i));
    }

    for(int i = 0; i < PASS_BYTE_SIZE; i++){
        dataBuffer[PASS_START_POS + i] = PASS[i];
        Println(DEBUG_MESSAGE_HEADER + "copied " + String(PASS[i]) + " to " + String(PASS_START_POS + i));
    }

    dataBuffer[CHECKSUM_POS] = calculateChecksum();
    Println(DEBUG_MESSAGE_HEADER + "calculated checksum = " + String(dataBuffer[CHECKSUM_POS]));

    updateMemberVariable();
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
