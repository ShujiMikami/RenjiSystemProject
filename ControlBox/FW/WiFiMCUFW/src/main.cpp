#include <Arduino.h>

#include "DebugMessageManager.h"
#include "MainSequencer.h"

void setup() 
{
  // put your setup code here, to run once:

  //デバッグメッセージ切り替え
  DebugMessageManager::MessageManage();

  MainSequencer::Setup();
}

void loop()
{
  // put your main code here, to run repeatedly:
  MainSequencer::Loop();
}
