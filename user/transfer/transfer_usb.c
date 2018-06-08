#include "transfer_usb.h"


#if defined (THROUGHPUT_BY_USB)



#pragma location = ".ccram"
uint8_t usbSendBuff[8192];


#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
   
__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;





void usbTransferInit(void)
{
    USBD_Init(&USB_OTG_dev,
#ifdef USE_USB_OTG_HS 
    USB_OTG_HS_CORE_ID,
#else            
    USB_OTG_FS_CORE_ID,
#endif  
    &USR_desc, 
    &USBD_CDC_cb, 
    &USR_cb);
}


void transferThroughUsb(uint8_t *buff,uint16_t len)
{
    DCD_EP_Tx(&USB_OTG_dev,CDC_IN_EP,buff,len);
}








#endif