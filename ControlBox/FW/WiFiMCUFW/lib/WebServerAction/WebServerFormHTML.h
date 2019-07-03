#ifndef _WEBSERVERFORMHTML_H_
#define _WEBSERVERFORMHTML_H_

#include <Arduino.h>
#include <time.h>

const String Form_WiFiSetting = 
"<h1>Wi-Fi Settings</h1>"
"<form method='post'>"
"  <input type='text' name='ssid' placeholder='ssid'><br>"
"  <input type='text' name='pass' placeholder='pass'><br>"
"  <input type='submit'><br>"
"</form>";

const String SettingSentPage = 
"<h1>Wi-Fi Settings sent</h1>";

const String Form_SystemControl = "";

String CreateCurrentStatusHTML(String nameOfMode, double currentTemp, String nameOfEnvironmentJudge, time_t currentTime, byte switchState);


#endif