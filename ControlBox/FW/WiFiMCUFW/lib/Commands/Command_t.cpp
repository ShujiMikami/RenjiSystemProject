#include "Command_t.h"
#include "DebugPrintf.h"

#define PACKET_LENGTH_WITHOUT_CHECKSUM (FULL_PACKET_SIZE - CHECKSUM_BYTE_SIZE)

bool Command_t::DebugSwitch = false;

Command_t::Command_t(byte* dataArray, size_t arrayLength)
{
    for(size_t i = 0; i < FULL_PACKET_SIZE; i++){
        if(arrayLength > i){
            dataBuffer[i] = dataArray[i];
        }
        else{
            dataBuffer[i] = 0;
            Println(DEBUG_MESSAGE_HEADER + "out of data array index : i = " + String(i));
        }
    }
    updateMemberVariable();
}
Command_t::Command_t()
{
    for(int i = 0; i < FULL_PACKET_SIZE; i++){
        dataBuffer[i] = 0;
    }
    updateMemberVariable();
}
void Command_t::updateMemberVariable()
{
    commandCode = dataBuffer[COMMAND_CODE_POS];
    response = dataBuffer[RESPONSE_POS];
    checkSum = dataBuffer[CHECKSUM_POS];

    Println(DEBUG_MESSAGE_HEADER + "commandCode = " + String(commandCode));
    Println(DEBUG_MESSAGE_HEADER + "response = " + String(response));
    Println(DEBUG_MESSAGE_HEADER + "checkSum = " + String(checkSum));


    commandContentsValid = checkSumValidate();
}
bool Command_t::checkSumValidate()
{
    return (calculateChecksum() == checkSum);
}
byte Command_t::calculateChecksum()
{
    uint16_t sum = 0;
    for(int i = 0; i < PACKET_LENGTH_WITHOUT_CHECKSUM; i++){
        sum += (uint16_t)dataBuffer[i];
    }

    return (byte)sum;
}
void Command_t::Println(String message)
{
    if(DebugSwitch){
        PrintfDebugger::Println(message);
    }

}
int Command_t::GetBytes(byte* buffer, size_t bufferSize)
{
    int result = 0;

    if(bufferSize < FULL_PACKET_SIZE){
        Println(DEBUG_MESSAGE_HEADER + "buffer size too small");
    }else{
        for(int i = 0; i < FULL_PACKET_SIZE; i++){
            buffer[i] = dataBuffer[i];
            result++;
        }
    }

    return result;
}