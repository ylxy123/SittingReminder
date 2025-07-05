#ifndef __STIMER_H
#define __STIMER_H
#include "py32f002b_ll_tim.h"
#ifdef __cplusplus
extern "C" {
#endif

struct timer {
  uint32_t start;
  uint32_t interval;
};

extern  uint32_t uip_timer;

void timer_set(struct timer *t, uint32_t interval);
void timer_reset(struct timer *t);
void timer_restart(struct timer *t);
int8_t timer_expired(struct timer *t);


#ifdef __cplusplus
}
#endif

#endif 




