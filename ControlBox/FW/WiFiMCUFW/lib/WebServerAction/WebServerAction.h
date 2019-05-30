#ifndef _WEBSERVERACTION_H_
#define _WEBSERVERACTION_H_

typedef enum{
    WIFI_SETTING_MODE,
    WIFI_RUN_MODE
}WiFiActionMode_t;


void Setup_WebServer(WiFiActionMode_t actionMode);
void Loop_WebServer();


#endif