#ifndef INTERNALDATAEXCHANGER_H_
#define INTERNALDATAEXCHANGER_H_

#include <Arduino.h>
#include "CageStatus.h"



class InternalDataExchanger{
public:
    typedef enum{
        ACK_RECEIVED,
        ERROR_OCCURED,
        NO_REPLY
    }Status_t;
public:
    static bool DebugSwitch;

public:
    static Status_t NotifyWiFiSetupModeLaunched(String SSID, String PASS);
    static Status_t NotifyWiFiSetupReceivedFromHost();
    static Status_t NotifyWiFiRouterConnectionResult(bool connectionResult);
    static Status_t GetCageStatus(CageStatus_t& cageStatusBuf);
private:
    InternalDataExchanger();
    static void Println(String message);
};


#endif