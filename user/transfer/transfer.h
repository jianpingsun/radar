#ifndef __TRANSFER_H
#define __TRANSFER_H

#include "conf.h"
#include "ucos_ii.h"

#if defined (THROUGHPUT_BY_ETH)
    #include "transfer_eth.h"
    
    #define startTranser  transferThroughEth
#elif defined (THROUGHPUT_BY_USB)
    #include "transfer_usb.h"

    #define stratTransfer transferThroughUsb 
#endif



#define TASK_HANDLE_CHANNEL1_DATA_PRIO              (1)
#define TASK_HANDLE_CHANNEL1_STK_SIZE               (256)


#define TASK_HANDLE_CHANNEL2_DATA_PRIO              (2)
#define TASK_HANDLE_CHANNEL2_STK_SIZE               (256)


#define TASK_TRANSFER_PRIO                          (OS_LOWEST_PRIO - 2)
#define TASK_TRANSFER_STK_SIZE                      (256)

#define SEND_BUFF_SIZE                              (4096)

#if defined (ADC1_ENABLE)
void taskHandleChannel1Data(void *para);
#endif

#if defined (ADC1_ENABLE)
void taskHandleChannel2Data(void *para);
#endif

void taskTranfer(void *para);





#endif