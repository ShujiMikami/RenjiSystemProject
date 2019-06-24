#include <Arduino.h>

#include "MainSequencer.h"
#include "Test_UARTCom.h"
#include "UARTCom.h"

void setup() 
{
  // put your setup code here, to run once:
  
  UARTComTest::Setup();
  //MainSequencer::Setup();
}

void loop()
{
  // put your main code here, to run repeatedly:
  //UARTComTest::Loop();
  //MainSequencer::Loop();
}
