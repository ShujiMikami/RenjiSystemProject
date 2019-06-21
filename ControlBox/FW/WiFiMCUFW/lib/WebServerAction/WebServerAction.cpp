#include "WebServerAction.h"
#include "WiFiHTTPServer.h"
#include "WebServerFormHTML.h"
#include "DebugPrintf.h"
#include <FS.h>

const char* WebServerAction::settingFileName = "/settings.txt";
bool WebServerAction::isFileSystemInitialized = false;

WebServerAction::WiFiActionMode_t WebServerAction::Setup(WiFiActionMode_t actionMode)
{
    WiFiActionMode_t result = actionMode;

    if(actionMode == WIFI_SETTING_MODE){
        WiFiHTTPServer::Setup_AP(callBackGET_WiFiSet, callBackPOST_WiFiSet);
    }else{
        HostInfo_t hostInfo = readHostInfoFromFlash();
        String storedSSID = hostInfo.GetSSID();
        String storedPass = hostInfo.GetPass();

        PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "read SSID : " + storedSSID + ", " + "read PASS : " + storedPass);

        bool connectionTryResult = WiFiHTTPServer::Setup(callBackGET_SystemControl, callBackPOST_SystemControl, storedSSID, storedPass);
        if(!connectionTryResult){
            WiFiHTTPServer::Setup_AP(callBackGET_WiFiSet, callBackPOST_WiFiSet);
            result = WIFI_SETTING_MODE;
        }
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

    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "Got SSID, PASS = " + ssid + ", " + pass);

    writeHostInfoToFile(ssid, pass);
    
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "Wrote ssid and pass to file");

    server.send(200, "text/html", SettingSentPage);

    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "Sent page");
}
void WebServerAction::callBackGET_WiFiSet(ESP8266WebServer& server)
{
    server.send(200, "text/html", Form_WiFiSetting);
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "Sent WiFi setting form");
}

void WebServerAction::callBackPOST_SystemControl(ESP8266WebServer& server)
{
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "Received WiFi setting");
}
void WebServerAction::callBackGET_SystemControl(ESP8266WebServer& server)
{
    server.send(200, "text/html", Form_SystemControl);
    PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "Sent system control form");
}

void WebServerAction::writeHostInfoToFile(String ssid, String pass)
{
    if(!isFileSystemInitialized){
        bool result = SPIFFS.begin();

        isFileSystemInitialized = true;

        if(result){
            PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "SPIFFS started ");
        }else{
            PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "SPIFFS mount failed ");
        }

    }

    File file = SPIFFS.open(settingFileName, "w");

    if(!file){
        PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "file open error");
    }

    file.println(ssid);
    file.println(pass); 

    file.close();
}
HostInfo_t WebServerAction::readHostInfoFromFlash()
{
    if(!isFileSystemInitialized){
        SPIFFS.begin();
        isFileSystemInitialized = true;
    }

    File file = SPIFFS.open(settingFileName, "r");

    if(!file){
        PrintfDebugger::Println(DEBUG_MESSAGE_HEADER + "file open error");
    }

    String ssid = file.readStringUntil('\n');
    String pass = file.readStringUntil('\n');
    file.close();

    return HostInfo_t(ssid, pass);
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
