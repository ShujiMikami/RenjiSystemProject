#include "WebServerFormHTML.h"


String CreateCurrentStatusHTML(CageStatus_t cageStatus)
{
    String html = "<h1>CurrentStatus</h1><br>";

    //current mode
    html += ("<h2>Current Mode : " + cageStatus.GetModeByString() + "</h2>" + "<br>");

    //current temperature
    html += ("<h2>Current Temperature : " + String(cageStatus.GetTemperature()) + "</h2>" + "<br>");

    //current judgement
    html += ("<h2>Current Judgement : " + cageStatus.GetEnvironmentJudgeByString() + "</h2>"  + "<br>");

    //current time
    time_t currentTime = time(0);
    struct tm* tm;
    tm = localtime(&currentTime);
    
    html += ("<h2>Current time : " + String(1900 + tm->tm_year) + "/" + String(1 + tm->tm_mon) + "/" + String(tm->tm_mday) + "/" + String(tm->tm_hour) + ":" + String(tm->tm_min) + "</h2>" + "<br>");

    //current switch
    html += ("<h2>SW1 state : " + String(cageStatus.GetSwitchStatus() & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW2 state : " + String((cageStatus.GetSwitchStatus() >> 1) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW3 state : " + String((cageStatus.GetSwitchStatus() >> 2) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW4 state : " + String((cageStatus.GetSwitchStatus() >> 3) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW5 state : " + String((cageStatus.GetSwitchStatus() >> 4) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW6 state : " + String((cageStatus.GetSwitchStatus() >> 5) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW7 state : " + String((cageStatus.GetSwitchStatus() >> 6) & 0x01) + "</h2>" + "<br>");
    html += ("<h2>SW8 state : " + String((cageStatus.GetSwitchStatus() >> 7) & 0x01) + "</h2>" + "<br>");

    return html;
}