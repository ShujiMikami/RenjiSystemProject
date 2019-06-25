#include "UARTCom.h"
#include "FormatInfo.h"
#include "DebugPrintf.h"

 
#define BUFFER_LENGTH (FULL_PACKET_SIZE)

static const uint32_t SERIAL_BAUDRATE = 115200;
static const uint32_t UART_RECEIVE_TIMEOUT = 50;

static byte receiveBuffer[BUFFER_LENGTH];
static int receivedCount = 0;
static HardwareSerial* pSerialForUARTCom = &Serial;

bool UARTCom::DebugSwitch = false;

void UARTCom::Setup()
{
    pSerialForUARTCom->begin(SERIAL_BAUDRATE);
    Println(DEBUG_MESSAGE_HEADER + "UARTCom Setup OK");
}
void UARTCom::Loop()
{
    if(receivedCount < BUFFER_LENGTH){
        //受信処理
        receiveProcess();
        
        //タイムアウト処理
        checkReceiveTimeout();
    }
}
bool UARTCom::NewCommandAvailable()
{
    return (receivedCount >= BUFFER_LENGTH);
}
int UARTCom::GetReceivedData(byte* buffer, size_t bufferSize)
{
    if(bufferSize < BUFFER_LENGTH){
        Println(DEBUG_MESSAGE_HEADER + "buffer size is too small");
    }else{
        for(size_t i = 0; i < bufferSize; i++){
            buffer[i] = receiveBuffer[i];
        }
        receivedCount = 0;
    }

    return bufferSize;
}
void UARTCom::SendData(byte* data, int numOfBytesToSend)
{

}

int UARTCom::transmitDataToBuffer(byte* data, int numOfBytesToTransmit)
{
    int countTransmitted = 0;

    for(int i = 0; i < numOfBytesToTransmit; i++){
        if(receivedCount < BUFFER_LENGTH){
            receiveBuffer[getPositionToWrite()] = data[i];
            receivedCount++;
            countTransmitted++;
        }
    }

    return countTransmitted;
}
inline int UARTCom::getPositionToWrite()
{
    return receivedCount;
}
void UARTCom::checkReceiveTimeout()
{
    static bool isReceiveStarted = false;
    static uint32_t timeOutStartEdge = 0;

    if(!isReceiveStarted){
        if(0 < receivedCount && receivedCount < BUFFER_LENGTH){
            Println(DEBUG_MESSAGE_HEADER + "receive stated");
            isReceiveStarted = true;
            timeOutStartEdge = millis();
        }
    }else if(receivedCount == BUFFER_LENGTH){
        isReceiveStarted = false;
    }else{
        if(millis() - timeOutStartEdge > UART_RECEIVE_TIMEOUT){
            Println(DEBUG_MESSAGE_HEADER + "TimeoutOccured");
            receivedCount = 0;
            isReceiveStarted = false;
        }
    }
}
void UARTCom::receiveProcess()
{
    //受信処理
    size_t bufferedLength = pSerialForUARTCom->available();

    //バッファリング処理
    if(bufferedLength > 0){
        Println(DEBUG_MESSAGE_HEADER + String(bufferedLength) + "bytes message received");
        byte readData[BUFFER_LENGTH];
        pSerialForUARTCom->readBytes(readData, bufferedLength);
        transmitDataToBuffer(readData, bufferedLength);
    }
}
void UARTCom::Println(String message)
{
    if(DebugSwitch){
        PrintfDebugger::Println(message);
    }
}