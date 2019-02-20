#include "APP_GPIO.h"
#include "cmsis_os.h"
#include "Printf4Debug.h"

#define QUEUE_DEPTH 10

typedef struct 
{
    /* data */
    GPIO_TypeDef* gpioPort;
    uint16_t gpioPin;
    GPIO_PinState gpioState;
}GPIO_State_t;


xQueueHandle GPIOWriteQueue;
osThreadId GPIOWriteTaskhandle;

static uint32_t period_ms = 10;
static uint32_t stableCount = 10;
#define STABLE_COUNT_LIMIT (2 * stableCount)

static void start_GPIO_Write_Task(const void* argument);

void APP_GPIO_Init()
{
    GPIOWriteQueue = xQueueCreate(QUEUE_DEPTH, sizeof(GPIO_State_t));
    
    osThreadDef(GPIO_WriteTask, start_GPIO_Write_Task, osPriorityNormal, 0, 128);
    GPIOWriteTaskhandle = osThreadCreate(osThread(GPIO_WriteTask), NULL);
}
void APP_GPIO_Write(GPIO_TypeDef* gpioPort, uint16_t gpioPin, GPIO_PinState gpioState)
{
    GPIO_State_t queueItem;

    queueItem.gpioPort = gpioPort;
    queueItem.gpioPin = gpioPin;
    queueItem.gpioState = gpioState;

    xQueueSendToBack(GPIOWriteQueue, &queueItem, portMAX_DELAY);
}
GPIO_PinState APP_GPIO_Read(GPIO_TypeDef* gpioPort, uint16_t gpioPin, boolean_t antiChattering)
{
    GPIO_PinState result = HAL_GPIO_ReadPin(gpioPort, gpioPin);

    if(antiChattering == TRUE){
        uint32_t count = 0;
        uint32_t count_OK = 0;

        GPIO_PinState latestResult = result;

        while(1){
            osDelay(period_ms);

            latestResult = HAL_GPIO_ReadPin(gpioPort, gpioPin);

            if(result == latestResult){
                count_OK++;
                break;
            }

            result = latestResult;

            if(++count > STABLE_COUNT_LIMIT){
                Printf4Debug("[Error]GPIO Input unstable.");
                break;
            }
        }
    }
    
    return result;
}
void APP_GPIO_SetChatteringParam(uint32_t period_ms, uint32_t bufferingTime_ms)
{

}
void start_GPIO_Write_Task(const void* argument)
{
    GPIO_State_t buffer;

    while(1){
        xQueueReceive(GPIOWriteQueue, &buffer, portMAX_DELAY);

        HAL_GPIO_WritePin(buffer.gpioPort, buffer.gpioPin, buffer.gpioState);
    }
}