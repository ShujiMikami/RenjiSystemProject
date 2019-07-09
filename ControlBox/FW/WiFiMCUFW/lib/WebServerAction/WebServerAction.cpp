#include "WebServerAction.h"
#include "WiFiHTTPServer.h"
#include "WebServerFormHTML.h"
#include "DebugPrintf.h"
#include <FS.h>
#include "Commands.h"
#include "InternalDataExchanger.h"

const char* WebServerAction::settingFileName = "/settings.txt";
bool WebServerAction::isFileSystemInitialized = false;

bool WebServerAction::DebugSwitch = false;

int WebServerAction::event = 0;

static Command_t eventArg = Command_t();

static String systemControlRequests[] = { "/sysset", "/currentStatus"};
static int systemControlRequestsCount = 2;
static String wifiSetRequests[] = { "/", "/currentStatus", "/sysset"};
static int wifiSetRequestsCount = 3;

WebServerAction::WiFiActionMode_t WebServerAction::Setup(WiFiActionMode_t actionMode)
{
    WiFiActionMode_t result = actionMode;

    if(actionMode == WIFI_SETTING_MODE){
        WiFiHTTPServer::Setup_AP(wifiSetRequests, wifiSetRequestsCount, callBackGET_WiFiSet, callBackPOST_WiFiSet);

        InternalDataExchanger::NotifyWiFiSetupModeLaunched(WiFiHTTPServer::GetSSID(), WiFiHTTPServer::GetPASS());

        //event = WiFiSetupCommand::CommandCode;
        //eventArg = (Command_t)WiFiSetupCommand(WiFiHTTPServer::GetSSID(), WiFiHTTPServer::GetPASS());
    }else if(actionMode == WIFI_RUN_MODE){
        HostInfo_t hostInfo = readHostInfoFromFlash();
        String storedSSID = hostInfo.GetSSID();
        String storedPass = hostInfo.GetPass();

        Println(DEBUG_MESSAGE_HEADER + "read SSID : " + storedSSID + ", " + "read PASS : " + storedPass);

        bool connectionTryResult = WiFiHTTPServer::Setup(systemControlRequests, systemControlRequestsCount, callBackGET_SystemControl, callBackPOST_SystemControl, storedSSID, storedPass);
        if(!connectionTryResult){
            WiFiHTTPServer::WiFi_Stop();
            result = WIFI_STOP_MODE;
        }


        //event = WiFiRouterConnectionCommand::CommandCode;
        //eventArg = (Command_t)WiFiRouterConnectionCommand((byte)connectionTryResult);
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

    //event = WiFiSettingReceivedCommand::CommandCode;
    InternalDataExchanger::NotifyWiFiSetupReceivedFromHost();
}
void WebServerAction::callBackGET_WiFiSet(ESP8266WebServer& server)
{
    String uri = server.uri();
    Println(DEBUG_MESSAGE_HEADER + "URI = " + uri);
    if(uri == wifiSetRequests[0]){
        server.send(200, "text/html", Form_WiFiSetting);
        Println(DEBUG_MESSAGE_HEADER + "Sent WiFi setting form");
    }else if(uri == wifiSetRequests[1]){
        //event = CageStatusGetCommand::CommandCode;
        server.send(200, "text/html", CreateCurrentStatusHTML("ModeA", 25.0, "Natural Cooling", time(0), 0x7F));
    }else if(uri == wifiSetRequests[2]){
        server.send(200, "text/html", Form_SystemControl);
    }
}

void WebServerAction::callBackPOST_SystemControl(ESP8266WebServer& server)
{
    Println(DEBUG_MESSAGE_HEADER + "Received system setting");
}
void WebServerAction::callBackGET_SystemControl(ESP8266WebServer& server)
{
    String uri = server.uri();
    if(uri == systemControlRequests[0]){
        server.send(200, "text/html", Form_SystemControl);
        Println(DEBUG_MESSAGE_HEADER + "Sent system control form");
    }else if(uri == systemControlRequests[1]){
        server.send(200, "text/html", CreateCurrentStatusHTML("ModeA", 25.0, "Natural Cooling", time(0), 0x7F));
    }
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
void WebServerAction::SendCageStatusHTML(ESP8266WebServer& server, String activateModeName, double currentTemperature, String environmentJudgeName, uint8_t switchStatus)
{
    server.send(200, "text/html", CreateCurrentStatusHTML(activateModeName, currentTemperature, environmentJudgeName, time(0), switchStatus));
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

