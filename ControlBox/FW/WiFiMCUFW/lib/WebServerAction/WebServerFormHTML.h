#ifndef _WEBSERVERFORMHTML_H_
#define _WEBSERVERFORMHTML_H_

#include <Arduino.h>

const String Form_WiFiSetting = 
"<h1>Wi-Fi Settings</h1>"
"<form method='post'>"
"  <input type='text' name='ssid' placeholder='ssid'><br>"
"  <input type='text' name='pass' placeholder='pass'><br>"
"  <input type='submit'><br>"
"</form>";

const String Form_SystemControl = "";




#endif