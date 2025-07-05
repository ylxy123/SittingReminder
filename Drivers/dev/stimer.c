#include "stimer.h"
//#include "segger_rtt.h"
uint32_t uip_timer;

void timer_set(struct timer *t, uint32_t interval)
{
  t->interval = interval;
  t->start = uip_timer;
}

void timer_reset(struct timer *t)
{
  t->start += t->interval;
}

void timer_restart(struct timer *t)
{
  t->start = uip_timer;
}

int8_t timer_expired(struct timer *t)
{
  if(uip_timer>=t->start)
    {
		if((uip_timer - t->start)>=t->interval)
		return 1;
		else
		return 0; 
	}
	else
	{
		if((0XFFFFFFFF - t->start+uip_timer)>=t->interval)
		return 1;
		else
		return 0;
	}
}
