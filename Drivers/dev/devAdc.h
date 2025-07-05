#ifndef __DEVADC_H
#define __DEVADC_H
#include "stddef.h"
#include "main.h"
#include "devUart.h"



extern void dev_adc_init(void);
extern uint32_t APP_AdcConvert(uint32_t channel);

#endif 




