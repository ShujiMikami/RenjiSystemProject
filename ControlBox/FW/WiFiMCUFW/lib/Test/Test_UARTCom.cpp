#include "Test_UARTCom.h"
#include "UARTCom.h"

void UARTComTest::Setup()
{
    UARTCom::DebugSwitch = true;
    UARTCom::Setup();
}
void UARTComTest::Loop()
{
    UARTCom::Loop();
}
