#include "WiFiSettingReceivedCommand.h"
#include "FormatInfo.h"
#include "DebugPrintf.h"

WiFiSettingReceivedCommand::WiFiSettingReceivedCommand(byte* dataArray, size_t arrayLength) : Command_t(dataArray, arrayLength)
{
    if(commandContentsValid){//チェックサムOKの場合は, コマンドコードが正しいかチェックする
        Println(DEBUG_MESSAGE_HEADER + "checkSum is OK");
        commandContentsValid = (commandCode == CommandCode);
        Println(DEBUG_MESSAGE_HEADER + "Command Validation result = " + String(commandContentsValid));
    }
}
WiFiSettingReceivedCommand::WiFiSettingReceivedCommand()
{
    dataBuffer[COMMAND_CODE_POS] = CommandCode;

    dataBuffer[CHECKSUM_POS] = calculateChecksum();
    Println(DEBUG_MESSAGE_HEADER + "calculated checksum = " + String(dataBuffer[CHECKSUM_POS]));

    updateMemberVariable();
}
WiFiSettingReceivedCommand::WiFiSettingReceivedCommand(Command_t command)
{
    byte byteData[FULL_PACKET_SIZE];

    command.GetBytes(byteData, FULL_PACKET_SIZE);

    *this = WiFiSettingReceivedCommand(byteData, FULL_PACKET_SIZE);

}