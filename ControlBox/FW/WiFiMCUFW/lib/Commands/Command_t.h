#ifndef _COMMANDANALYZER_H_
#define _COMMANDANALYZER_H_

#include <Arduino.h>
#include "FormatInfo.h"


class Command_t{
public:
    Command_t(byte* dataArray, size_t arrayLength);
    Command_t();
    static bool DebugSwitch;
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