#include "WebServerAction.h"
#include "WiFiHTTPServer.h"
#include "WebServerFormHTML.h"
#include "DebugPrintf.h"
#include <FS.h>
#include "EventActions.h"
#include "Commands.h"

const char* WebServerAction::settingFileName = "/settings.txt";
bool WebServerAction::isFileSystemInitialized = false;

bool WebServerAction::DebugSwitch = false;

int WebServerAction::event = 0;

static Command_t eventArg = Command_t();

WebServerAction::WiFiActionMode_t WebServerAction::Setup(WiFiActionMode_t actionMode)
{
    WiFiActionMode_t result = actionMode;

    if(actionMode == WIFI_SETTING_MODE){
        WiFiHTTPServer::Setup_AP(callBackGET_WiFiSet, callBackPOST_WiFiSet);

        event = WiFiSetupCommandAction::eventCode;
        eventArg = (Command_t)WiFiSetupCommand(WiFiHTTPServer::GetSSID(), WiFiHTTPServer::GetPASS());
    }else if(actionMode == WIFI_RUN_MODE){
        HostInfo_t hostInfo = readHostInfoFromFlash();
        String storedSSID = hostInfo.GetSSID();
        String storedPass = hostInfo.GetPass();

        Println(DEBUG_MESSAGE_HEADER + "read SSID : " + storedSSID + ", " + "read PASS : " + storedPass);

        bool connectionTryResult = WiFiHTTPServer::Setup(callBackGET_SystemControl, callBackPOST_SystemControl, storedSSID, storedPass);
        if(!connectionTryResult){
            WiFiHTTPServer::WiFi_Stop();
            result = WIFI_STOP_MODE;
        }

        event = WiFiRouterConnectionCommandAction::eventCode;
        eventArg = (Command_t)WiFiRouterConnectionCommand((byte)connectionTryResult);
    }else if(actionMode == WIFI_STOP_MODE){
        WiFiHTTPServer::WiFi_Stop();
    }

    return result;
}
void WebServerAction::Loop()
{
    WiFiHTTPServer::LoopForWiFiInterface();
}

void WebServerAction::callBackPOST_WiFiSet(ESP8266WebServer& server)
{
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    Println(DEBUG_MESSAGE_HEADER + "Got SSID, PASS = " + ssid + ", " + pass);

    writeHostInfoToFile(ssid, pass);
    
    Println(DEBUG_MESSAGE_HEADER + "Wrote ssid and pass to file");

    server.send(200, "text/html", SettingSentPage);

    Println(DEBUG_MESSAGE_HEADER + "Sent page");

    event = WiFiSettingReceivedCommandAction::eventCode;
}
void WebServerAction::callBackGET_WiFiSet(ESP8266WebServer& server)
{
    server.send(200, "text/html", Form_WiFiSetting);
    Println(DEBUG_MESSAGE_HEADER + "Sent WiFi setting form");
}

void WebServerAction::callBackPOST_SystemControl(ESP8266WebServer& server)
{
    Println(DEBUG_MESSAGE_HEADER + "Received WiFi setting");
}
void WebServerAction::callBackGET_SystemControl(ESP8266WebServer& server)
{
    server.send(200, "text/html", Form_SystemControl);
    Println(DEBUG_MESSAGE_HEADER + "Sent system control form");
}

void WebServerAction::writeHostInfoToFile(String ssid, String pass)
{
    if(!isFileSystemInitialized){
        bool result = SPIFFS.begin();

        if(result){
            isFileSystemInitialized = true;
        }
        else{
            Println(DEBUG_MESSAGE_HEADER + "SPIFFS start error");
        }
    }

    File file = SPIFFS.open(settingFileName, "w");

    if(!file){
        Println(DEBUG_MESSAGE_HEADER + "file open error");
    }

    file.println(ssid);
    file.println(pass); 

    file.close();
}
HostInfo_t WebServerAction::readHostInfoFromFlash()
{
    if(!isFileSystemInitialized){
        bool result = SPIFFS.begin();

        if(result){
            isFileSystemInitialized = true;
        }
        else{
            Println(DEBUG_MESSAGE_HEADER + "SPIFFS start error");
        }
    }

    File file = SPIFFS.open(settingFileName, "r");

    if(!file){
        Println(DEBUG_MESSAGE_HEADER + "file open error");
    }

    String ssid = file.readStringUntil('\n');
    String pass = file.readStringUntil('\n');
    file.close();

    return HostInfo_t(ssid, pass);
}
void WebServerAction::Println(String message)
{
    if(DebugSwitch){
        PrintfDebugger::Println(message);
    }
}
int WebServerAction::GetEvent()
{
    int result = event;

    event = 0;

    return result;
}
int WebServerAction::PeekEvent()
{
    return event;
}
Command_t WebServerAction::GetEventArg()
{
    return eventArg;
}

HostInfo_t::HostInfo_t(String ssidToSet, String passToSet)
{
    ssid = ssidToSet;
    pass = passToSet;
}
String HostInfo_t::GetSSID()
{
    return ssid;
}
String HostInfo_t::GetPass()
{
    return pass;
}
