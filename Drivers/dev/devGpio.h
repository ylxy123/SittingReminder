#ifndef __DEVGPIO_H
#define __DEVGPIO_H
#include "stddef.h"
#include "dev.h"


extern void dev_gpio_init(void);

extern void dev_gpio_le_mode(void);

extern void power_5V_off(void);
extern void power_5V_on(void);
#endif 




