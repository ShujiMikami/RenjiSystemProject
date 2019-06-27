#ifndef _COMMAND_T_H_
#define _COMMAND_T_H_

#include <Arduino.h>
#include "FormatInfo.h"


class Command_t{
public:
    Command_t(byte* dataArray, size_t arrayLength);
    Command_t();
    static bool DebugSwitch;
    int GetBytes(byte* buffer, size_t bufferSize);
    byte GetCommandCode();
    byte GetResponse();
    byte GetCheckSum();
    bool IsValidCommand();
protected:
    byte dataBuffer[FULL_PACKET_SIZE];
    byte commandCode;
    byte response;
    byte checkSum;
    bool commandContentsValid;
protected:
    void updateMemberVariable();
    bool checkSumValidate();
    byte calculateChecksum();
    void Println(String message);
};



#endif