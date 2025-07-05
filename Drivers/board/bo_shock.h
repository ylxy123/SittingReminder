#ifndef __BO_SHOCK_H
#define __BO_SHOCK_H

#include "stdint.h"
#include "dev.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SHOCK_FILTER_TICK_TA   (1000)

typedef struct
{
  uint16_t tick;
  uint16_t tickTa;
  uint8_t flag;
  uint8_t state;
}shock_tick_info_t;


typedef struct
{
   uint8_t state;
}shock_ori_info_t;

  
typedef struct
{
   uint8_t          result;
  shock_tick_info_t tick;
}shock_filter_info_t;


typedef struct
{
    shock_ori_info_t  ori;
  shock_filter_info_t filter;
}shock_info_t;
  
extern shock_info_t boShock;

extern void bo_shock_init(void);
extern void bo_shock_filter_state_update(shock_info_t *s);
extern uint8_t bo_shock_filter_result_get(shock_info_t *s);
extern void bo_shock_tick_rstart(shock_info_t *s,shock_tick_info_t timer);
extern void bo_shock_state_set(shock_info_t *s,uint8_t state);

#ifdef __cplusplus
}
#endif

#endif 

