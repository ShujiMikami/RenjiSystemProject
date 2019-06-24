#include "Command_t.h"

#define PACKET_LENGTH_WITHOUT_CHECKSUM (FULL_PACKET_SIZE - CHECKSUM_BYTE_SIZE)

Command_t::Command_t(byte* dataArray, size_t arrayLength)
{
    for(int i = 0; i < FULL_PACKET_SIZE; i++){
        if(arrayLength < i + 1){
            dataBuffer[i] = dataArray[i];
        }
        else{
            dataBuffer[i] = 0;
        }
    }
    updateMemberVariable();
}
void Command_t::updateMemberVariable()
{
    commandCode = dataBuffer[COMMAND_CODE_POS];
    response = dataBuffer[RESPONSE_POS];
    checkSum = dataBuffer[CHECKSUM_POS];

    commandContentsValid = checkSumValidate();
}
bool Command_t::checkSumValidate()
{
    bool result = false;

    uint16_t sum = 0;
    for(int i = 0; i < PACKET_LENGTH_WITHOUT_CHECKSUM; i++){
        sum += (uint16_t)dataBuffer[i];
    }

    result = ((byte)sum == checkSum);

    return result;
}