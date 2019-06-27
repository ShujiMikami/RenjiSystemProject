#include "CageStatusGetCommand.h"
#include "FormatInfo.h"
#include "DebugPrintf.h"

const int ACTIVATIONMODE_START_POS = DATA_START_POS;
const int ACTIVATIONMODE_BYTE_SIZE = 1;
const int CURRENTTEMPERATURE_START_POS = ACTIVATIONMODE_START_POS + ACTIVATIONMODE_BYTE_SIZE;
const int CURRENTTEMPERATURE_BYTE_SIZE = 2;
const int ENVIRONMENTJUDGEMENT_START_POS = CURRENTTEMPERATURE_START_POS + CURRENTTEMPERATURE_BYTE_SIZE;
const int ENVIRONMENTJUDGEMENT_BYTE_SIZE = 1;
const int INTERNALTIME_START_POS = ENVIRONMENTJUDGEMENT_START_POS + ENVIRONMENTJUDGEMENT_BYTE_SIZE;
const int INTERNALTIME_BYTE_SIZE = 4;
const int SWITCH_STATUS_START_POS = INTERNALTIME_START_POS + INTERNALTIME_BYTE_SIZE;
const int SWITCH_STATUS_BYTE_SIZE = 1;

CageStatusGetCommand::CageStatusGetCommand(byte* dataArray, size_t arrayLength) : Command_t(dataArray, arrayLength)
{
    if(commandContentsValid){//チェックサムOKの場合は, コマンドコードが正しいかチェックする
        Println(DEBUG_MESSAGE_HEADER + "checkSum is OK");
        commandContentsValid = (commandCode == CommandCode);
        Println(DEBUG_MESSAGE_HEADER + "Command Validation result = " + String(commandContentsValid));
    }
}
CageStatusGetCommand::CageStatusGetCommand()
{
    dataBuffer[COMMAND_CODE_POS] = CommandCode;

    dataBuffer[CHECKSUM_POS] = calculateChecksum();
    Println(DEBUG_MESSAGE_HEADER + "calculated checksum = " + String(dataBuffer[CHECKSUM_POS]));

    updateMemberVariable();
}
byte CageStatusGetCommand::GetActivationMode()
{
    return dataBuffer[ACTIVATIONMODE_START_POS];
}
uint16_t CageStatusGetCommand::GetCurrentTemperature()
{
    uint16_t result = 0;

    for(int i = 0; i < CURRENTTEMPERATURE_BYTE_SIZE; i++){
        result |= ((uint16_t)dataBuffer[CURRENTTEMPERATURE_START_POS + i] << ((CURRENTTEMPERATURE_BYTE_SIZE - i - 1) * 8));
    }

    return result;
}
byte CageStatusGetCommand::GetEnvironmentJudgement()
{
    return dataBuffer[ENVIRONMENTJUDGEMENT_START_POS];
}
uint32_t CageStatusGetCommand::GetInternalTime()
{
    uint32_t result = 0;

    for(int i = 0; i < INTERNALTIME_BYTE_SIZE; i++){
        result |= ((uint32_t)dataBuffer[INTERNALTIME_START_POS + i] << ((INTERNALTIME_BYTE_SIZE - i - 1) * 8));
    }

    return result;
}
byte CageStatusGetCommand::GetSwitchStatus()
{
    return dataBuffer[SWITCH_STATUS_START_POS];
}
CageStatusGetCommand::CageStatusGetCommand(Command_t command)
{
    byte byteData[FULL_PACKET_SIZE];

    command.GetBytes(byteData, FULL_PACKET_SIZE);

    *this = CageStatusGetCommand(byteData, FULL_PACKET_SIZE);
} 