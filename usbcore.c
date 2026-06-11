#include "stm32f4xx.h"

void usb_core_init(void)
{
    // 1. Enable USB clock
    RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
    volatile uint32_t dummy = RCC->AHB2ENR;

    // 2. Power up PHY
    USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_PWRDWN;

    // 3. Force device mode
    USB_OTG_FS->GUSBCFG |= USB_OTG_GUSBCFG_FDMOD;

    // 4. Core reset
    USB_OTG_FS->GRSTCTL |= USB_OTG_GRSTCTL_CSRST;
    while (USB_OTG_FS->GRSTCTL & USB_OTG_GRSTCTL_CSRST);

    // 5. Set Full Speed
    USB_OTG_FS_DEVICE->DCFG &= ~USB_OTG_DCFG_DSPD;
    USB_OTG_FS_DEVICE->DCFG |= USB_OTG_DCFG_DSPD_0;

    // 6. Flush RX FIFO
    USB_OTG_FS->GRSTCTL |= USB_OTG_GRSTCTL_RXFFLSH;
    while (USB_OTG_FS->GRSTCTL & USB_OTG_GRSTCTL_RXFFLSH);

    // 7. Enable interrupts
    USB_OTG_FS->GAHBCFG |= USB_OTG_GAHBCFG_GINT;
    USB_OTG_FS->GINTMSK |= USB_OTG_GINTMSK_USBRSTM;

    // 8. Disable VBUS sensing
    USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_NOVBUSSENS;
}