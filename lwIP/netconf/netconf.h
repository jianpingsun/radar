#ifndef __NETCONF_H
#define __NETCONF_H



#include <stdint.h>
#include "lwip/ip_addr.h"

#define DEVICE_NAME 								"TEST_ABC123"
 
//#define USE_DHCP

#define FACTORY_SET_PARA_ADDR						(0x0807F400)
#define DEVICE_CONFIG_PARA_ADDR						(0x0807F000)

#define MAX_DHCP_TRIES                          0x04

#define DHCP_START                              0x00
#define DHCP_WAIT_ADDRESS                       0x01
#define DHCP_ADDRESS_ASSIGNED                   0x02
#define DHCP_TIMEOUT                            0x03
#define DHCP_LINK_DOWN                          0x04


#define DEFAULT_BROADCAST_IP0                      	255
#define DEFAULT_BROADCAST_IP1                      	255
#define DEFAULT_BROADCAST_IP2                      	255
#define DEFAULT_BROADCAST_IP3                      	255

#define DEFAULT_REMOTE_IP0                      	192
#define DEFAULT_REMOTE_IP1                      	168
#define DEFAULT_REMOTE_IP2                      	1
#define DEFAULT_REMOTE_IP3                      	166

#define DEFAULT_IP0                             	192
#define DEFAULT_IP1                             	168
#define DEFAULT_IP2                             	1
#define DEFAULT_IP3                             	252

#define DEFAULT_NETMASK0                        	255
#define DEFAULT_NETMASK1                        	255
#define DEFAULT_NETMASK2                        	255
#define DEFAULT_NETMASK3                        	0


#define DEFAULT_GATEWAY0                        	192  
#define DEFAULT_GATEWAY1                        	168
#define DEFAULT_GATEWAY2                        	1
#define DEFAULT_GATEWAY3                        	1

#define DEVICE_BROADCAST_PORT                   	16500
#define DEFAULT_UDP_485_PORT                    	16501
#define DEFAULT_UDP_CAN1_PORT						16502
#define DEFAULT_UDP_CAN2_PORT						16503
#define DEFAULT_UDP_GPIO_PORT						16504

#define DEFAULT_TELNET_PORT                     	23


struct LWIPDevice
{
	union
	{
		uint8_t remoteIP[4];
		struct ip_addr remoteIP_s;
	}RemoteIP;
	union
	{
		uint8_t deviceIP[4];
		struct ip_addr deviceIP_s;
	}DeviceIP;
	union
	{
		uint8_t netMask[4];
		struct ip_addr netMask_s;
	}NetMask;
	union
	{
		uint8_t gateWay[4];
		struct ip_addr gateWay_s;
	}GateWay;
    uint32_t broadcastPort;
};


struct RS485Device
{
	uint32_t speed;
	uint32_t port;
};

struct CANDevice
{
	uint32_t speed;
	uint32_t port;
};

struct GPIODevice
{
	uint32_t data;
	uint16_t sendCycle;
	uint16_t port;
};



struct DeviceConfiguration
{
	char Name[20];
	struct LWIPDevice 	lwipDevice;
	struct RS485Device 	rs485Device;
	struct CANDevice 	CanDevice[2];
	struct GPIODevice	gpioDevice;
	uint32_t flag;
};



void lwipInit();
void LwIP_Pkt_Handle(void);
void LwIP_Periodic_Handle(uint32_t localtime);










#endif