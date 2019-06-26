#include "Test_UARTCom.h"
#include "UARTCom.h"

void UARTComTest::Setup()
{
    UARTCom::DebugSwitch = true;
    UARTCom::Setup();
}
void UARTComTest::Loop()
{
    /* 
    UARTCom::Loop();

    if(UARTCom::NewCommandAvailable()){
        byte buffer[256];

        UARTCom::GetReceivedData(buffer, sizeof(buffer));
    }
    */
   byte data[] = { 0, 1, 2, 3};
   byte buffer[10];
   UARTCom::SendDataAndReceive(data, sizeof(data), buffer, sizeof(buffer), 4000);

   delay(1000);
}
