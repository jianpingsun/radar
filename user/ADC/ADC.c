#include "ADC.h"
#include "ucos_ii.h"
#include "conf.h"

#if defined (ADC1_ENABLE)
extern OS_EVENT *channel1Updated;
uint16_t ADC1DmaBuffer[2][ADC_DMA_BUFFER_SIZE];
uint16_t *currBuff1Ptr;
uint8_t buff1Updated = 0;
#endif

#if defined (ADC2_ENABLE)
extern OS_EVENT *channel2Updated;
uint16_t ADC2DmaBuffer[2][ADC_DMA_BUFFER_SIZE];
uint16_t *currBuff2Ptr;
uint8_t buff2Updated = 0;
#endif

static void ADCGpioConfig()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC->AHB1ENR |= ADC_GPIO_PORT_CLK;

    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin     = ADC_GPIO_PIN1 | ADC_GPIO_PIN2;

    GPIO_Init(ADC_GPIO_PORT,&GPIO_InitStructure); 

}


static void ADCTrigTimerConfig()
{
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    
    RCC->APB1ENR |= RCC_APB1Periph_TIM2;
    
    TIM_InitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Prescaler         = 0;
    TIM_InitStructure.TIM_Period            = 299;

    TIM_TimeBaseInit(TIM2,&TIM_InitStructure);

    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

    TIM_Cmd(TIM2,ENABLE);
}

static void ADCDmaConfig()
{
    DMA_InitTypeDef DMA_InitStructure;

    RCC->AHB1ENR |= RCC_AHB1Periph_DMA2;
#if defined (ADC1_ENABLE)
/********************CONFIG DMA2 STREAM 0 CHANNEL0 FOR ADC1**********************/
    DMA_InitStructure.DMA_Channel                       = DMA_Channel_0;
    DMA_InitStructure.DMA_PeripheralBaseAddr            = (uint32_t)&(ADC1->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr               = (uint32_t)(&ADC1DmaBuffer[0][0]);
    DMA_InitStructure.DMA_DIR                           = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize                    = ADC_DMA_BUFFER_SIZE;
    DMA_InitStructure.DMA_PeripheralInc                 = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc                     = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize            = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize                = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode                          = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority                      = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode                      = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold                 = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst                   = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst               = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);

    DMA_DoubleBufferModeConfig(DMA2_Stream0,(uint32_t)(&ADC1DmaBuffer[1][0]),DMA_Memory_0);
    DMA_DoubleBufferModeCmd(DMA2_Stream0,ENABLE);
    
    DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TC); 
    DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);   
    DMA_Cmd(DMA2_Stream0, ENABLE);
#endif
/********************CONFIG DMA2 STREAM 2 CHANNEL0 FOR ADC2**********************/
#if defined (ADC2_ENABLE)
    DMA_InitStructure.DMA_Channel                       = DMA_Channel_1;
    DMA_InitStructure.DMA_PeripheralBaseAddr            = (uint32_t)&(ADC2->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr               = (uint32_t)(&ADC2DmaBuffer[0][0]);
    DMA_InitStructure.DMA_DIR                           = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize                    = ADC_DMA_BUFFER_SIZE;
    DMA_InitStructure.DMA_PeripheralInc                 = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc                     = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize            = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize                = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode                          = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority                      = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode                      = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold                 = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst                   = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst               = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream2, &DMA_InitStructure);
    
    DMA_DoubleBufferModeConfig(DMA2_Stream2,(uint32_t)(&ADC2DmaBuffer[1][0]),DMA_Memory_0);
    DMA_DoubleBufferModeCmd(DMA2_Stream2,ENABLE);
    
    DMA_ClearITPendingBit(DMA2_Stream2, DMA_IT_TC); 
    DMA_ITConfig(DMA2_Stream2, DMA_IT_TC, ENABLE);   
    DMA_Cmd(DMA2_Stream2, ENABLE);
#endif
}

static void ADCNvicConfig()
{
    NVIC_InitTypeDef NVIC_InitStructure;
#if defined (ADC1_ENABLE)
    NVIC_InitStructure.NVIC_IRQChannel                      = DMA2_Stream0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 1;     
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;   
    NVIC_Init(&NVIC_InitStructure); 
#endif
#if defined (ADC2_ENABLE)
    NVIC_InitStructure.NVIC_IRQChannel                      = DMA2_Stream2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE; 
    NVIC_Init(&NVIC_InitStructure); 
#endif
}

static void ADCConfig()
{
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef       ADC_InitStructure;
#if defined (ADC1_ENABLE)
    RCC->APB2ENR |= RCC_APB2Periph_ADC1;
#endif
#if defined (ADC2_ENABLE)
    RCC->APB2ENR |= RCC_APB2Periph_ADC2
#endif
      
#if defined (ADC1_ENABLE) || defined (ADC2_ENABLE)
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles; 
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
    ADC_CommonInit(&ADC_CommonInitStructure);
    
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  
    ADC_InitStructure.ADC_NbrOfConversion = 1;
#endif
#if defined (ADC1_ENABLE)
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_28Cycles);
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
#endif
#if defined (ADC2_ENABLE)
    ADC_Init(ADC2, &ADC_InitStructure);
    ADC_RegularChannelConfig(ADC2, ADC_Channel_1, 1, ADC_SampleTime_28Cycles);
    ADC_DMARequestAfterLastTransferCmd(ADC2, ENABLE);
    ADC_DMACmd(ADC2, ENABLE);
    ADC_Cmd(ADC2, ENABLE);
#endif
}

void ADCInit()
{
    ADCGpioConfig();
    ADCTrigTimerConfig();
    ADCDmaConfig();
    ADCNvicConfig();
    ADCConfig();
}


#if defined (ADC1_ENABLE)
void DMA2_Stream0_IRQHandler()  
{
    OSIntEnter();
    if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))
    {
        buff1Updated = 1;
        if(DMA_GetCurrentMemoryTarget(DMA2_Stream0) == DMA_Memory_0)
        {
            currBuff1Ptr = &ADC1DmaBuffer[0][0];
        }
        else
        {
            currBuff1Ptr = &ADC1DmaBuffer[1][0];
        }
        OSSemPost(channel1Updated);
        DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
    }
    OSIntExit();
}
#endif

#if defined (ADC2_ENABLE)
void DMA2_Stream2_IRQHandler()  
{
    OSIntEnter();
    if(DMA_GetITStatus(DMA2_Stream2, DMA_IT_TCIF2))
    {
        buff2Updated = 1;
        if(DMA_GetCurrentMemoryTarget(DMA2_Stream2) == DMA_Memory_0)
        {
            currBuff2Ptr = &ADC2DmaBuffer[0][0];
        }
        else
        {
            currBuff2Ptr = &ADC2DmaBuffer[1][0];
        }
        OSSemPost(channel2Updated);
        DMA_ClearITPendingBit(DMA2_Stream2, DMA_IT_TCIF2);
    }
    OSIntExit();
}
#endif