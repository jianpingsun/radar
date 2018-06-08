#ifndef __TRANSFER_USB_H
#define __TRANSFER_USB_H

#include "conf.h"



#if defined (THROUGHPUT_BY_USB)


#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"


void usbTransferInit(void);
void transferThroughUsb(uint8_t *buff,uint16_t len);


#endif


#endif