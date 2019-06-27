#include "EventHandler.h"
#include "DebugPrintf.h"

#define EVENT_REGISTER_MAX_COUNT 50

const static int EVENT_CODE_UPPER_LIMIT = EVENT_REGISTER_MAX_COUNT - 1;

const static int NOT_REGISTERED = EVENT_REGISTER_MAX_COUNT;

static int eventCodeArray[EVENT_REGISTER_MAX_COUNT];
static int reverseArray[EVENT_REGISTER_MAX_COUNT];
static void (*funcPtr[EVENT_REGISTER_MAX_COUNT])();

static int eventRegisteredCount = 0;

bool EventHandler::DebugSwitch = false;

void EventHandler::Setup()
{
    for(int i = 0; i < EVENT_REGISTER_MAX_COUNT; i++){
        eventCodeArray[i] = NOT_REGISTERED;
        reverseArray[i] = NOT_REGISTERED;
        funcPtr[i] = nullptr;
    }
}

bool EventHandler::RegisterEvent(int eventCode, void (*callBack)())
{
    bool result = true;

    //登録可能かどうかチェック
    if(!checkEventCodeRegisterable(eventCode)){
        result = false;
    }else{
        eventCodeArray[eventRegisteredCount] = eventCode;
        reverseArray[eventCode] = eventRegisteredCount;
        funcPtr[eventRegisteredCount] = callBack;
        eventRegisteredCount++;
    }

    return result;
}
void EventHandler::ExecuteEvent(int eventCode)
{
    if(isCallBackRegistered(eventCode)){
        Println(DEBUG_MESSAGE_HEADER + "call back index for event code " + String(eventCode) + " found(" + String(reverseArray[eventCode]) + ")");
        funcPtr[reverseArray[eventCode]]();
    }
}
bool EventHandler::checkEventCodeRegisterable(int eventCode)
{
    bool result = true;

    if(eventRegisteredCount > EVENT_CODE_UPPER_LIMIT){
        result = false;
    }else{
        for(int i = 0; i < eventRegisteredCount; i++){
            if(eventCode == eventCodeArray[i]){
                result = false;
                break;
            }
        }
    }
    return result;
}
void EventHandler::Println(String message)
{
    if(DebugSwitch){
        PrintfDebugger::Println(message);
    }
}
bool EventHandler::isCallBackRegistered(int eventCode)
{
    return (reverseArray[eventCode] <= EVENT_CODE_UPPER_LIMIT && funcPtr[reverseArray[eventCode]] != nullptr);
}