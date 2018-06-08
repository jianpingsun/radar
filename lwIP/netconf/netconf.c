#include "stm32f4xx.h"
#include "stm32f4x7_eth.h"
#include "netconf.h"
#include "ethernetif.h"
#include "lwip/tcp.h"
#include "lwip/tcp_impl.h"
#include "lwip/init.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include <stdio.h>
#include <string.h>



//global device configuration parameter structure
#pragma pack(4)
struct DeviceConfiguration Device;
#pragma pack()

#pragma pack(4)
volatile struct DeviceConfiguration FactorySet =
{
	.Name 				= DEVICE_NAME,
	.lwipDevice 		= {
								{DEFAULT_REMOTE_IP0,DEFAULT_REMOTE_IP1,DEFAULT_REMOTE_IP2,DEFAULT_REMOTE_IP3},
								{DEFAULT_IP0,DEFAULT_IP1,DEFAULT_IP2,DEFAULT_IP3},
								{DEFAULT_NETMASK0,DEFAULT_NETMASK1,DEFAULT_NETMASK2,DEFAULT_NETMASK3},
								{DEFAULT_GATEWAY0,DEFAULT_GATEWAY1,DEFAULT_GATEWAY2,DEFAULT_GATEWAY3},
								{DEVICE_BROADCAST_PORT}
						  },
	.rs485Device 		= {115200,DEFAULT_UDP_485_PORT},
	.CanDevice[0] 		= {500,DEFAULT_UDP_CAN1_PORT},
	.CanDevice[1]		= {500,DEFAULT_UDP_CAN2_PORT},
	.gpioDevice			= {0x0000,100,DEFAULT_UDP_GPIO_PORT},
	.flag 				= 0x00000000
};
#pragma pack()

#ifdef USE_DHCP
static void LwIP_DHCP_Process_Handle();
#endif

struct netif netif;
uint32_t TCPTimer = 0;
uint32_t ARPTimer = 0;

#ifdef USE_DHCP
uint32_t DHCPfineTimer = 0;
uint32_t DHCPcoarseTimer = 0;
#endif

void lwipInit()
{
    lwip_init();   //init used modules
#ifdef USE_DHCP
    ipaddr.addr = 0;
    netmask.addr = 0;
    gw.addr = 0;
#endif
    memcpy((uint8_t *)&Device,(uint8_t *)&FactorySet,sizeof(FactorySet));
	netif_add(&netif, &Device.lwipDevice.DeviceIP.deviceIP_s, &Device.lwipDevice.NetMask.netMask_s, &Device.lwipDevice.GateWay.gateWay_s, NULL, &ethernetif_init, &ethernet_input);
    netif_set_default(&netif);
    netif_set_up(&netif);
}





void LwIP_Pkt_Handle(void)
{
    ethernetif_input(&netif);
}


void LwIP_Periodic_Handle(__IO uint32_t localtime)
{
#if LWIP_TCP
    /* TCP periodic process every 250 ms */
    if (localtime - TCPTimer >= TCP_TMR_INTERVAL)
    {
      TCPTimer =  localtime;
      tcp_tmr();
    }
#endif
    /* ARP periodic process every 5s */
    if ((localtime - ARPTimer) >= ARP_TMR_INTERVAL)
    {
      ARPTimer =  localtime;
      etharp_tmr();
    }

#ifdef USE_DHCP
    /* Fine DHCP periodic process every 500ms */
    if (localtime - DHCPfineTimer >= DHCP_FINE_TIMER_MSECS)
    {
      DHCPfineTimer =  localtime;
      dhcp_fine_tmr();
      if ((lwipDevice0.DHCPStatus != DHCP_ADDRESS_ASSIGNED) && 
          (lwipDevice0.DHCPStatus != DHCP_TIMEOUT) &&
            (lwipDevice0.DHCPStatus != DHCP_LINK_DOWN))
      { 
        /* process DHCP state machine */
        LwIP_DHCP_Process_Handle();    
      }
    }
    /* DHCP Coarse periodic process every 60s */
    if (localtime - DHCPcoarseTimer >= DHCP_COARSE_TIMER_MSECS)
    {
      DHCPcoarseTimer =  localtime;
      dhcp_coarse_tmr();
    }
  
#endif
}

#ifdef USE_DHCP
/**
  * @brief  LwIP_DHCP_Process_Handle
  * @param  None
  * @retval None
  */
void LwIP_DHCP_Process_Handle()
{
    struct ip_addr ipaddr;
    struct ip_addr netmask;
    struct ip_addr gw;

    switch (lwipDevice0.DHCPStatus)
    {
      case DHCP_START:
      {
          dhcp_start(&netif);
          ipaddr.addr = 0;
          lwipDevice0.DHCPStatus = DHCP_WAIT_ADDRESS;
      }
      break;
      case DHCP_WAIT_ADDRESS:
      {
        /* Read the new IP address */
          ipaddr = netif.ip_addr;
          netmask = netif.netmask;
          gw = netif.gw;
          if (ipaddr.addr != 0) 
          {
              lwipDevice0.DHCPStatus = DHCP_ADDRESS_ASSIGNED;
              lwipDevice0.deviceIP[3] = ipaddr.addr >> 24;
              lwipDevice0.deviceIP[2] = ipaddr.addr >> 16;
              lwipDevice0.deviceIP[1] = ipaddr.addr >> 8;
              lwipDevice0.deviceIP[0] = ipaddr.addr >> 0;
              
              lwipDevice0.gateWay[3] = gw.addr >> 24;
              lwipDevice0.gateWay[2] = gw.addr >> 16;
              lwipDevice0.gateWay[1] = gw.addr >> 8;
              lwipDevice0.gateWay[0] = gw.addr >> 0;
              
              lwipDevice0.netMask[3] = netmask.addr >> 24;
              lwipDevice0.netMask[2] = netmask.addr >> 16;
              lwipDevice0.netMask[1] = netmask.addr >> 8;
              lwipDevice0.netMask[0] = netmask.addr >> 0;
              /* Stop DHCP */
              dhcp_stop(&netif);
          }
          else
          {
            /* DHCP timeout */
              if (netif.dhcp->tries > MAX_DHCP_TRIES)
              {
                  lwipDevice0.DHCPStatus = DHCP_TIMEOUT;
                  dhcp_stop(&netif);
                  IP4_ADDR(&ipaddr,lwipDevice0.deviceIP[0],lwipDevice0.deviceIP[1],lwipDevice0.deviceIP[2],lwipDevice0.deviceIP[3]);
                  IP4_ADDR(&netmask,lwipDevice0.netMask[0],lwipDevice0.netMask[1],lwipDevice0.netMask[2],lwipDevice0.netMask[3]);
                  IP4_ADDR(&gw,lwipDevice0.gateWay[0],lwipDevice0.gateWay[1],lwipDevice0.gateWay[2],lwipDevice0.gateWay[3]);
                  netif_set_addr(&netif, &ipaddr , &netmask, &gw);
              }
          }
      }
      break;
      default: break;
    }
}
#endif      


void ETH_IRQHandler(void)
{                        
    /* Clear the Eth DMA Rx IT pending bits */
    while(ETH_CheckFrameReceived())
    { 
        LwIP_Pkt_Handle();
    }
    ETH_DMAClearITPendingBit(ETH_DMA_IT_R);
    ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);
}
