#include <Arduino.h>
#include "TaskMessager.h"
#include "app_LEDToggle.h"
#include "app_WiFiAPScan.h"
#include "app_SPIMaster.h"

typedef enum{
  NO_BYTES_RECEIVED,
  TIMEOUT_OCCURED,
  CHECKSUM_INVALID,
  VALID_BYTES_RECEIVED
}BytesReceivedStatus;


const uint32_t MESSAGE_DELAY = 1000;
const String TASK_NAME = "MainTask";

static uint8_t dataBuffer[500];
static int receivedCount = 0;

static void setup_Communication();
static BytesReceivedStatus loop_Communication();

static bool headerDetected = false;

static bool checkStartFromCommandByte();

static bool checksumVaild();

void setup() 
{
  // put your setup code here, to run once:
  setup_Communication();
}

void loop()
{
  // put your main code here, to run repeatedly:
  loop_Communication();
  

}

void setup_Communication()
{
  Serial.begin(115200);
}
BytesReceivedStatus loop_Communication()
{
  static uint32_t headerDetectedCount = 0;

  BytesReceivedStatus result = NO_BYTES_RECEIVED;

  //バイト受信
  int remainingBytes = Serial.available();
  if(remainingBytes > 0){
    Serial.read((char*)&dataBuffer[receivedCount], remainingBytes);
    receivedCount += remainingBytes;
  }

  //受信バイトバリデーション
  int byteCount = 0;
  if(!headerDetected){
    if(receivedCount > 2){
       if(!checkStartFromCommandByte()){//0xA0から開始してたら
        headerDetected = true;//受信中に遷移
        headerDetectedCount = millis();//受信時刻取得
      }
      else{
        receivedCount = 0;//受信結果を無効化
        result = NO_BYTES_RECEIVED;
      }
    }
  }
  else{
    uint32_t timeElapsed = millis() - headerDetectedCount;

    if(receivedCount >= byteCount){//受信予定バイト数受信してたら
      if(checksumVaild()){//チェックサムが一致してたら
        result = VALID_BYTES_RECEIVED;
      }
      else{
        result = CHECKSUM_INVALID;
      }
      receivedCount = 0;
    }
    else{
      if(timeElapsed > 50){//50msec以上空いたら
        result = TIMEOUT_OCCURED;
        receivedCount = 0;
      }
    }
  }


  if(receivedCount > 0){
    if(!headerDetected){//コマンドパケットヘッダ受信前
      if(!checkStartFromCommandByte()){//0xA0から開始してたら
        headerDetected = true;//受信中に遷移
        headerDetectedCount = millis();//受信時刻取得
      }
      else{
        receivedCount = 0;//受信結果を無効化
        result = NO_BYTES_RECEIVED;
      }
    }
    else{//コマンドパケットヘッダ受信済み
      uint32_t timeElapsed = millis() - headerDetectedCount;

      if(receivedCount >= 2){//バイトカウントまで受信してたら
        int byteCount = dataBuffer[1];
     
        if(receivedCount >= byteCount){//受信予定バイト数受信してたら
          if(checksumVaild()){//チェックサムが一致してたら
            result = VALID_BYTES_RECEIVED;
          }
          else{
            result = CHECKSUM_INVALID;
          }
          receivedCount = 0;
        }
        else{
          if(timeElapsed > 50){//50msec以上空いたら
            result = TIMEOUT_OCCURED;
            receivedCount = 0;
          }
        }
      }
      else{
        if(timeElapsed > 50){//50msec以上空いたら
          result = TIMEOUT_OCCURED;
          receivedCount = 0;
        }
      }
    }
  }

  return result;
}

bool checkStartFromCommandByte()
{
  return (dataBuffer[0] == 0xA0);
}

bool checksumVaild()
{
  return true;
}