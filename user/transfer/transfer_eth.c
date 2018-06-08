#include "transfer_eth.h"

#if defined (THROUGHPUT_BY_ETH)

#define UDP_PORT                    5500

#define LWIP_UDP_SEND_BUFF          4096
#define LWIP_UDP_RECV_BUFF          4096  

uint8_t udpSendBuff[LWIP_UDP_SEND_BUFF];
uint8_t udpRecvBuff[LWIP_UDP_RECV_BUFF];

uint8_t udpSendFlag;

struct udp_pcb* udpPcb;






void udpRecv(void* arg,struct udp_pcb* upcb,struct pbuf* p,struct ip_addr*addr ,u16_t port)
{
    uint32_t len;
    struct pbuf *q = p;
    if(q!=NULL)
    {
        for(q = p; q; q = q->next)
        {
            if(q->len > (LWIP_UDP_RECV_BUFF - len))
            {
                memcpy(udpRecvBuff + len,q->payload,(LWIP_UDP_RECV_BUFF - len));
            }
            else
            {
                memcpy(udpRecvBuff + len,q->payload,q->len);
            }
            len += q->len;
            if(len > LWIP_UDP_RECV_BUFF)
              return;
        }
        pbuf_free(p);
    } 
}


void udpSend(struct udp_pcb *pcb,uint8_t *Buff,uint16_t len)
{
    struct pbuf *p;
	p = pbuf_alloc(PBUF_TRANSPORT,len,PBUF_RAM);
	if(p)
	{
		pbuf_take(p,Buff,len);
		udp_send(pcb,p);
		pbuf_free(p);
	} 
}



void udpInit(void)
{
    ip_addr_t ipaddr;
    IP4_ADDR(&ipaddr, 192, 168, 1, 101); 
    udpPcb = udp_new();
    if(udpPcb!=NULL)
    {
        udp_bind(udpPcb,IP_ADDR_ANY,UDP_PORT);
        udp_connect(udpPcb,&ipaddr,UDP_PORT);
        udp_recv(udpPcb,udpRecv,NULL); 
    }
}


void transferThroughEth(uint8_t *buff,uint16_t len)
{
    udpSend(udpPcb,buff,len);
}


#endif



