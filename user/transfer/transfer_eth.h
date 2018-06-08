#ifndef __TRANSFER_ETH_H
#define __TRANSFER_ETH_H



#include "conf.h"


#if defined (THROUGHPUT_BY_ETH)


#include "stm32f4x7_eth.h"
#include "stm32f4x7_eth_bsp.h"
#include "netconf.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"



void udpInit(void);
void transferThroughEth(uint8_t *buff,uint16_t len);




#endif


#endif