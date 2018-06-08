#include "APP.h"
#include "ucos_ii.h"
#include "transfer.h"


#pragma location = ".ccram"
OS_STK taskStartStk[TASK_START_STK_SIZE];

#pragma location = ".ccram"
OS_STK taskLed0Stk[TASK_LED0_STK_SIZE];


extern OS_STK taskHandleChannel1Stk[TASK_HANDLE_CHANNEL1_STK_SIZE];
extern OS_STK taskHandleChannel2Stk[TASK_HANDLE_CHANNEL2_STK_SIZE];
extern OS_STK taskTransferStk[TASK_TRANSFER_STK_SIZE];


static void LEDGpioConfig();
static void taskLed0(void *para);


void taskStart(void *para)
{
    INT8U err;
    LEDGpioConfig();
    OSStatInit();
    err = OSTaskCreateExt(taskLed0, (void *)0, (OS_STK *)&taskLed0Stk[TASK_LED0_STK_SIZE - 1], TASK_LED0_PRIO, TASK_LED0_PRIO,
                          (OS_STK *)&taskLed0Stk[0], TASK_LED0_STK_SIZE, (void *)0, OS_TASK_OPT_STK_CHK);
    OSTaskNameSet(TASK_LED0_PRIO, "taskLED0", &err);
    
#if defined (ADC1_ENABLE)
    err = OSTaskCreateExt(taskHandleChannel1Data, (void *)0, (OS_STK *)&taskHandleChannel1Stk[TASK_HANDLE_CHANNEL1_STK_SIZE - 1], TASK_HANDLE_CHANNEL1_DATA_PRIO, TASK_HANDLE_CHANNEL1_DATA_PRIO,
                          (OS_STK *)&taskHandleChannel1Stk[0], TASK_HANDLE_CHANNEL1_STK_SIZE, (void *)0, OS_TASK_OPT_STK_CHK);
    OSTaskNameSet(TASK_HANDLE_CHANNEL1_DATA_PRIO, "taskHandleChannel1", &err);
#endif
    
#if defined (ADC2_ENABLE)
    err = OSTaskCreateExt(taskHandleChannel2Data, (void *)0, (OS_STK *)&taskHandleChannel2Stk[TASK_HANDLE_CHANNEL2_STK_SIZE - 1], TASK_HANDLE_CHANNEL2_DATA_PRIO, TASK_HANDLE_CHANNEL2_DATA_PRIO,
                          (OS_STK *)&taskHandleChannel2Stk[0], TASK_HANDLE_CHANNEL2_STK_SIZE, (void *)0, OS_TASK_OPT_STK_CHK);
    OSTaskNameSet(TASK_HANDLE_CHANNEL2_DATA_PRIO, "taskHandleChannel2", &err);
#endif
    
    err = OSTaskCreateExt(taskTranfer, (void *)0, (OS_STK *)&taskTransferStk[TASK_TRANSFER_STK_SIZE - 1], TASK_TRANSFER_PRIO, TASK_TRANSFER_PRIO,
                          (OS_STK *)&taskTransferStk[0], TASK_TRANSFER_STK_SIZE, (void *)0, OS_TASK_OPT_STK_CHK);
    OSTaskNameSet(TASK_TRANSFER_PRIO, "taskTransfer", &err);
    
    OSTaskDel(TASK_START_PRIO);   
}



void taskLed0(void *para)
{
    for(;;)
    {
        GPIOH->ODR ^= GPIO_Pin_2;
        OSTimeDlyHMSM (0, 0, 0, 500);
    }
}



void LEDGpioConfig()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC->AHB1ENR |= RCC_AHB1Periph_GPIOH;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOH, &GPIO_InitStructure);
    GPIOE->ODR |= GPIO_Pin_2 | GPIO_Pin_3;
}