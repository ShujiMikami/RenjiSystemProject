#ifndef _COMMANDANALYZER_H_
#define _COMMANDANALYZER_H_

#include <Arduino.h>

class Command_t{
public:
    Command_t(byte* dataArray, size_t arrayLength);

private:


};

class CommandAnalyzer{
public:
private:
    CommandAnalyzer();
    static bool validateBytes(byte* dataArray, size_t arrayLength);
};


#endif