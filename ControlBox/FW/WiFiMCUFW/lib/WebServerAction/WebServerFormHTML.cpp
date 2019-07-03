#include "WebServerFormHTML.h"


String CreateCurrentStatusHTML(String nameOfMode, double currentTemp, String nameOfEnvironmentJudge, time_t currentTime, byte switchState)
{
    String html = "<h1>CurrentStatus</h1><br>";

    //current mode
    html += ("<h2>Current Mode : " + nameOfMode + "</h2>" + "<br>");

    //current temperature
    html += ("<h2>Current Temperature : " + String(currentTemp) + "</h2>" + "<br>");

    //current judgement
    html += ("<h2>Current Judgement : " + nameOfEnvironmentJudge + "</h2>"  + "<br>");

    //current time
    struct tm* tm;
    tm = localtime(&currentTime);
    
    html += ("<h2>Current time : " + String(1900 + tm->tm_year) + "/" + String(1 + tm->tm_mon) + "/" + String(tm->tm_mday) + "/" + String(tm->tm_hour) + ":" + String(tm->tm_min) + "</h2>" + "<br>");

    //current switch
    html += ("<h2>SW1 state : " + String(switchState & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW2 state : " + String((switchState >> 1) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW3 state : " + String((switchState >> 2) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW4 state : " + String((switchState >> 3) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW5 state : " + String((switchState >> 4) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW6 state : " + String((switchState >> 5) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW7 state : " + String((switchState >> 6) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW8 state : " + String((switchState >> 7) & 0x01) + "</h2>" + "<br>");

    return html;
}