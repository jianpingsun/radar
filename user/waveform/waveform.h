#ifndef __WAVEFORM_H
#define __WAVEFORM_H


#include "stm32f4xx.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"

#define SAMPLE_SIZE             (1000)




void waveformOutputDacInit();













#endif