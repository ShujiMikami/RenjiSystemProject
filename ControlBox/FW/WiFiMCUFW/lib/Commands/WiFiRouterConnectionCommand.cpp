#include "WiFiRouterConnectionCommand.h"
#include "FormatInfo.h"
#include "DebugPrintf.h"

const int CONNECTION_STATUS_START_POS = DATA_START_POS;
const int CONNECTION_STATUS_BYTE_SIZE = 1; 

WiFiRouterConnectionCommand::WiFiRouterConnectionCommand(byte* dataArray, size_t arrayLength) : Command_t(dataArray, arrayLength)
{
    if(commandContentsValid){//チェックサムOKの場合は, コマンドコードが正しいかチェックする
        Println(DEBUG_MESSAGE_HEADER + "checkSum is OK");
        commandContentsValid = (commandCode == CommandCode);
        Println(DEBUG_MESSAGE_HEADER + "Command Validation result = " + String(commandContentsValid));
    }
}
WiFiRouterConnectionCommand::WiFiRouterConnectionCommand(byte connectionStatus)
{
    dataBuffer[COMMAND_CODE_POS] = CommandCode;

    dataBuffer[CONNECTION_STATUS_START_POS] = connectionStatus;

    dataBuffer[CHECKSUM_POS] = calculateChecksum();
    Println(DEBUG_MESSAGE_HEADER + "calculated checksum = " + String(dataBuffer[CHECKSUM_POS]));

    updateMemberVariable();
}
byte WiFiRouterConnectionCommand::GetConnectionStatus()
{
    return dataBuffer[CONNECTION_STATUS_START_POS];
}