#ifndef COMMANDANALYZER_H_
#define COMMANDANALYZER_H_

#include "stm32f3xx_hal.h"

typedef enum{
    DATA_LENGTH_NOT_SATISFIED,
    CHECKSUM_INVALID,
    UNKOWN_COMMAND,
    VALID_COMMAND
}AnalyzedResult_t;

void CommandAnalyzer_Init();

#endif