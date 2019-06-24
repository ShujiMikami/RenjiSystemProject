#include "UARTCom.h"
#include "DebugPrintf.h"

 
#define BUFFER_LENGTH 66
#define SERIAL_BAUDRATE 115200

static byte receiveBuffer[BUFFER_LENGTH];
static int receivedCount = 0;
static HardwareSerial* pSerialForUARTCom = &Serial;

static int transmitDataToBuffer(byte* data, int numOfBytesToTransmit);
static inline int getPositionToWrite();
static void checkReceiveTimeout();
static void receiveProcess();

static const uint32_t UART_RECEIVE_TIMEOUT = 50;

void UARTCom::Setup()
{
    PrintfDebugger::Println("UARTCom Setup OK");
    pSerialForUARTCom->begin(SERIAL_BAUDRATE);
}
void UARTCom::Loop()
{
    //タイムアウト処理
    checkReceiveTimeout();

    //受信処理
    receiveProcess();

    //データ解析処理
    bool isValidCommandReceived = false;
    if(receivedCount == BUFFER_LENGTH){
        PrintfDebugger::Println("received bytes");
    }

    //コマンド応答
    if(isValidCommandReceived){

    }
}
int UARTCom::GetReceivedCount()
{
    return 0;

}
int UARTCom::GetReceivedData(byte* buffer, int numOfBytesToRead)
{
    return 0;
}
void UARTCom::SendData(byte* data, int numOfBytesToSend)
{

}

int transmitDataToBuffer(byte* data, int numOfBytesToTransmit)
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
inline int getPositionToWrite()
{
    return receivedCount;
}
void checkReceiveTimeout()
{
    static bool isReceiveStarted = false;
    static uint32_t timeOutStartEdge = 0;

    if(!isReceiveStarted){
        if(0 < receivedCount && receivedCount < BUFFER_LENGTH){
            isReceiveStarted = true;
            timeOutStartEdge = millis();
        }
    }else{
        if(millis() - timeOutStartEdge > UART_RECEIVE_TIMEOUT){
            PrintfDebugger::Println("TimeoutOccured");
            receivedCount = 0;
            isReceiveStarted = false;
        } 
    }
}
void receiveProcess()
{
    //受信処理
    size_t bufferedLength = pSerialForUARTCom->getRxBufferSize();

    //バッファリング処理
    if(bufferedLength > 0){
        byte readData[BUFFER_LENGTH];
        pSerialForUARTCom->readBytes(readData, bufferedLength);
        transmitDataToBuffer(readData, bufferedLength);
    }
}