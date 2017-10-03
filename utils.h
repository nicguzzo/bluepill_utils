#ifndef _H_BLUEPILL_UTILS
#define _H_BLUEPILL_UTILS

#include "stm32f1xx_hal.h"
#include "usb_device.h"
#include "stm32f1xx_hal_rtc_ex.h"

void init_vector_table();
void set_reboot(uint8_t r);
void check_bootloader();
void reenumerate_usb();

#endif