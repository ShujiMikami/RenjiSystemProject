#include "SimpleRingBuffer.h"

SimpleRingBuffer CreateSimpleRingBuffer(uint8_t* pBuffer, uint16_t bufferLength)
{
    SimpleRingBuffer result;

    result.BufferPointer = pBuffer;
    result.BufferLength = bufferLength;
    result.DataCount = 0;
    result.ReadPosition = 0;

    return result;
}
void NotifyBufferEnd(SimpleRingBuffer* simpleRingBuffer)
{

}
uint16_t ReadDataFromBuffer(SimpleRingBuffer* uSimpleRingBuffer, uint8_t* buffer, uint16_t bufferLength)
{

}

