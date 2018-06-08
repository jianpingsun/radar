#ifndef __ADC_H
#define __ADC_H


#include "stm32f4xx.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"


#define ADC1_CLK                        (RCC_APB2Periph_ADC1)
#define ADC2_CLK                        (RCC_APB2Periph_ADC2)
#define ADC3_CLK                        (RCC_APB2Periph_ADC3)
#define ADC_DMA_BUFFER_SIZE             (1024)


#define ADC_GPIO_PORT                   (GPIOA)
#define ADC_GPIO_PORT_CLK               (RCC_AHB1Periph_GPIOA)
#define ADC_GPIO_PIN1                   (GPIO_Pin_0)
#define ADC_GPIO_PIN2                   (GPIO_Pin_1)









void ADCInit();









#endif
