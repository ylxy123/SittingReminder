#ifndef __DEV_H
#define __DEV_H
#include "stddef.h"

#include "devUart.h"
#include "devadc.h"
#include "devgpio.h"



extern void dev_init(void);

extern void APP_DelayNops(uint32_t Nops);
#endif 




