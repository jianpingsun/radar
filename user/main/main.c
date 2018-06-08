#include "main.h"


extern OS_STK taskStartStk[TASK_START_STK_SIZE];
extern struct fifo tFifo;

void testGPIOConfig()
{
    RCC->AHB1ENR |= RCC_AHB1Periph_GPIOE;
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
    
    GPIOE->ODR |= GPIO_Pin_2;
}


void bspConfig()
{
#if defined (THROUGHPUT_BY_ETH)
    ETH_BSP_Config();
#endif
    fifoInit(&tFifo,FIFO_SIZE);
    ADCInit();
    waveformOutputDacInit();
    SEGGER_RTT_ConfigUpBuffer(0, "RTTUP", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    SEGGER_RTT_ConfigDownBuffer(0, "RTTDOWN", NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
    testGPIOConfig();
}


void Delay(__IO uint32_t nCount)
{
    __IO uint32_t index = 0;
    for(index = nCount; index != 0; index--)
    {
    }
}




void main()
{
    INT8U err;
    bspConfig();
    OS_CPU_SysTickInit(192);
    OSInit();
    OSTaskCreateExt(taskStart, (void *)0, (OS_STK *)&taskStartStk[TASK_START_STK_SIZE - 1], TASK_START_PRIO, TASK_START_PRIO,
                              (OS_STK *)&taskStartStk[0], TASK_START_STK_SIZE, (void *)0, OS_TASK_OPT_STK_CHK);
    OSTaskNameSet(TASK_START_PRIO, "taskStart", &err);
    OSStart();
    while(1);
}