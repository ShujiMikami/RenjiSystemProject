#include <Arduino.h>

#include "MainSequencer.h"

void setup() 
{
  // put your setup code here, to run once:
  
  MainSequencer::Setup();
}

void loop()
{
  // put your main code here, to run repeatedly:

  MainSequencer::Loop();
}
