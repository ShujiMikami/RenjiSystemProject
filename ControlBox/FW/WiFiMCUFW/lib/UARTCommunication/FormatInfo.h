#ifndef FORMATINFO_H_
#define FORMATINFO_H_

typedef unsigned long uint32_t;
typedef unsigned char byte;

//共通
#define COMMAND_BYTE_SIZE 1
#define DATA_BYTE_SIZE 64
#define CHECKSUM_BYTE_SIZE 1
#define FULL_PACKET_SIZE (COMMAND_BYTE_SIZE + DATA_BYTE_SIZE + CHECKSUM_BYTE_SIZE)
byte GetResponse();


//WiFiセットアップモード遷移通知
const byte COMMANDCODE_WIFI_SETUP_NOTIFICATION = 0x01;
uint32_t GetSSID();
uint32_t GetPass();

//HostからのWiFi設定取得通知
const byte COMMANDCODE_WIFI_SETTING_RECEIVED_NOTIFICATION = 0x02;

//WiFiルータへの接続結果通知
const byte COMMANDCODE_WIFI_CONNECTION_RESULT = 0x03;
byte GetStatusCode();

//ケージのステータス要求
const byte COMMANDCODE_GET_CAGE_STATUS = 0x04;

//ケージのステータス返答
byte GetActivationMode();
byte GetCurrentTemperature();
byte GetEnvironmentJudge();
byte GetCurrentTime();
byte GetSwitchStatus();

//動作モード設定
const byte COMMANDCODE_SET_ACTIVATION_MODE = 0x05;
void SetActivationMode(byte activationMode);

//スイッチ状態設定
const byte COMMANDCODE_SET_SWITCH_STATUS = 0x06;
void SetSwitchStatus(byte switchStatus);





#endif