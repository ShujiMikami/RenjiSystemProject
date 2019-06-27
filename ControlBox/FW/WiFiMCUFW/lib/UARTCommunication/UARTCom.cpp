#include "UARTCom.h"
#include "DebugPrintf.h"

static const uint32_t SERIAL_BAUDRATE = 115200;
static HardwareSerial* pSerialForUARTCom = &Serial;

bool UARTCom::DebugSwitch = false;

void UARTCom::Setup()
{
    pSerialForUARTCom->begin(SERIAL_BAUDRATE);
    Println(DEBUG_MESSAGE_HEADER + "UARTCom Setup OK");
}
void UARTCom::Println(String message)
{
    if(DebugSwitch){
        PrintfDebugger::Println(message);
    }
}
void UARTCom::SendDataAndReceive(byte* data, size_t numOfBytesToSend, byte* receiveBuffer, size_t numOfBytesToReceive, int timeOut)
{
    pSerialForUARTCom->setTimeout(timeOut);

    pSerialForUARTCom->write(data, numOfBytesToSend);

    Println(DEBUG_MESSAGE_HEADER + "sent " + String(numOfBytesToSend) + " bytes");

    size_t receivedByteCount = pSerialForUARTCom->readBytes(receiveBuffer, numOfBytesToReceive);

    Println(DEBUG_MESSAGE_HEADER + "received " + String(receivedByteCount) + " bytes");
}
Command_t UARTCom::SendDataAndReceive(Command_t command, int timeOut)
{
    pSerialForUARTCom->setTimeout(timeOut);

    byte sendData[FULL_PACKET_SIZE];
    byte receiveBuf[FULL_PACKET_SIZE];

    int commandByteCount = command.GetBytes(sendData, sizeof(sendData));

    if(commandByteCount == FULL_PACKET_SIZE){
        SendDataAndReceive(sendData, sizeof(sendData), receiveBuf, sizeof(receiveBuf), timeOut);
    }

    return Command_t(receiveBuf, sizeof(receiveBuf));
}