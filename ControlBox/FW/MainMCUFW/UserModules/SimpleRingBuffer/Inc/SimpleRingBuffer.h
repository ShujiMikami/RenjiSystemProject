#ifndef _SIMPLERINGBUFFER_H_
#define _SIMPLERINGBUFFER_H_

#include <stdint.h>

typedef struct
{
    /* data */
    uint8_t* BufferPointer;
    uint16_t BufferLength;
    uint16_t ReadPosition;
    uint16_t DataCount;
}SimpleRingBuffer;

SimpleRingBuffer CreateSimpleRingBuffer(uint8_t* pBuffer, uint16_t bufferLength);
void NotifyBufferEnd(SimpleRingBuffer* simpleRingBuffer);
uint16_t ReadDataFromBuffer(SimpleRingBuffer* uSimpleRingBuffer, uint8_t* buffer, uint16_t bufferLength);

#endif