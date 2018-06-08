#ifndef __MAIN_H
#define __MAIN_H



#include "conf.h"
#include "transfer.h"
#include "app.h"
#include "fifo.h"
#include "ucos_ii.h"
#include "waveform.h"


#if defined (DO_FFT)
    #include "arm_math.h"
    #include "arm_const_structs.h"
#endif

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "ADC.h"
#include "SEGGER_RTT.h"
#include <stdio.h>
#include <math.h>




void Delay(uint32_t nCount);


#endif