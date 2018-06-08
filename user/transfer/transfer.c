#include "transfer.h"
#include "fifo.h"
#include "ADC.h"

#if defined (ADC1_ENABLE)
extern uint16_t ADC1DmaBuffer[2][ADC_DMA_BUFFER_SIZE];
extern uint16_t *currBuff1Ptr;
extern uint8_t buff1Updated;

#pragma location = ".ccram"
OS_STK taskHandleChannel1Stk[TASK_HANDLE_CHANNEL1_STK_SIZE];

OS_EVENT *channel1Updated;

#endif

#if defined (ADC2_ENABLE)
extern uint16_t ADC2DmaBuffer[2][ADC_DMA_BUFFER_SIZE];
extern uint16_t *currBuff2Ptr;
extern uint8_t buff2Updated;

#pragma location = ".ccram"
OS_STK taskHandleChannel2Stk[TASK_HANDLE_CHANNEL2_STK_SIZE];

OS_EVENT *channel2Updated;

#endif

extern struct fifo tFifo;
extern uint8_t txState;

extern void stratTransfer(uint8_t *buff,uint16_t len);



#pragma location = ".ccram"
OS_STK taskTransferStk[TASK_TRANSFER_STK_SIZE];

uint8_t sendBuff[SEND_BUFF_SIZE] = {0};

#if defined (DO_FFT)

uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;

#pragma location = ".ccram"
float fftInputBuffer[2048];
#pragma location = ".ccram"
float fftResultBuffer0[1024];
#pragma location = ".ccram"
float fftResultBuffer1[1024];

#endif


#if defined (ADC1_ENABLE)
void taskHandleChannel1Data(void *para)
{
    INT8U err;
    OS_CPU_SR cpu_sr;
    channel1Updated = OSSemCreate(0);
    for(;;)
    {
        OSSemPend(channel1Updated,0,&err);
        OS_ENTER_CRITICAL();
        if(buff1Updated == 1)
        {
            GPIOE->ODR ^= GPIO_Pin_2;
            buff1Updated = 0;
#if defined (DO_FFT)
            for(i = 0; i < FFT_SIZE; i++)
            {
                fftInputBuffer[2 * i] = *(currBuff1Ptr + i);
                fftInputBuffer[2 * i + 1] = 0;
            }
            arm_cfft_f32(&arm_cfft_sR_f32_len1024,fftInputBuffer,ifftFlag,doBitReverse);
            fifoPutData(&tFifo,(uint8_t *)currBuff1Ptr,4096);
            arm_cmplx_mag_f32(fftInputBuffer,fftResultBuffer0,fftSize);
            arm_cfft_f32(&arm_cfft_sR_f32_len1024,fftInputBuffer,ifftFlag,doBitReverse);
            fifoPutData(&tFifo,(uint8_t *)fftInputBuffer,4096);
            arm_cmplx_mag_f32(fftInputBuffer,fftResultBuffer1,fftSize);
#else 
            fifoPutData(&tFifo,(uint8_t *)currBuff1Ptr,ADC_DMA_BUFFER_SIZE * 2);
#endif
        }
        OS_EXIT_CRITICAL();
    }
}
#endif


#if defined (ADC2_ENABLE)
void taskHandleChannel2Data(void *para)
{
    INT8U err;
    OS_CPU_SR cpu_sr;
    channel2Updated = OSSemCreate(0);
    for(;;)
    {
        OSSemPend(channel2Updated,0,&err);
        OS_ENTER_CRITICAL();
        if(buff2Updated == 1)
        {
            GPIOE->ODR ^= GPIO_Pin_3;
            buff2Updated = 0;
#if defined (DO_FFT)
            for(i = 0; i < 1024; i++)
            {
                fftInputBuffer[2 * i] = *(currBuff2Ptr + i);
                fftInputBuffer[2 * i + 1] = 0;
            }
            arm_cfft_f32(&arm_cfft_sR_f32_len1024,fftInputBuffer,ifftFlag,doBitReverse);
            fifoPutData(&tFifo,(uint8_t *)currBuff2Ptr,4096);
            arm_cmplx_mag_f32(fftInputBuffer,fftResultBuffer0,fftSize);
            arm_cfft_f32(&arm_cfft_sR_f32_len1024,fftInputBuffer,ifftFlag,doBitReverse);
            fifoPutData(&tFifo,(uint8_t *)fftInputBuffer,4096);
            arm_cmplx_mag_f32(fftInputBuffer,fftResultBuffer1,fftSize);
#else
            fifoPutData(&tFifo,(uint8_t *)currBuff2Ptr,ADC_DMA_BUFFER_SIZE * 2);
#endif
        }
        OS_EXIT_CRITICAL();
    }
}
#endif


void taskTranfer(void *para)
{
    uint16_t dataLen = 0;
    OS_CPU_SR cpu_sr;
#if defined (THROUGHPUT_BY_ETH)
    udpInit();
#elif defined (THROUGHPUT_BY_USB)
    usbTransferInit();
    txState = 1;
    OSTimeDlyHMSM (0, 0, 1, 0);
#endif
    for(;;)
    {
        if(fifoGetLen(&tFifo) >= SEND_BUFF_SIZE)
        {
            dataLen = fifoGetData(&tFifo,sendBuff,SEND_BUFF_SIZE);
#if defined (THROUGHPUT_BY_USB)
            if((dataLen > 0) && (txState == 1))
            {
                OS_ENTER_CRITICAL();
                txState = 0;
                GPIOE->ODR ^= GPIO_Pin_4;
                stratTransfer(sendBuff,dataLen);
                OS_EXIT_CRITICAL();
            }
#endif
        }
    }
}

