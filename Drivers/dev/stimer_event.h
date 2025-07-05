#ifndef __STIMER_EVENT_H
#define __STIMER_EVENT_H
#include "py32f002b_ll_tim.h"
#include "stimer.h"
#include "py32f002b_ll_gpio.h"
#include "devtim.h"
#include "bsp.h"
#include "dev.h"
#include "core.h"
#ifdef __cplusplus
extern "C" {
#endif
extern void dev_timer_param_reinit(void);

extern void dev_timer_event_init(void);
extern void dev_timer_event_update_by_timer(void);
#ifdef __cplusplus
}
#endif

#endif 




