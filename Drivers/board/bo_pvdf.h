#ifndef __BO_PVDF_H
#define __BO_PVDF_H

#include "stdint.h"
#include "dev.h"
#include "bsp.h"
#include "th_lib.h"

#ifdef __cplusplus
extern "C" {
#endif



#define PVDF_THREADHOLD_ADC_1    (3000)
#define PVDF_THREADHOLD_ADC_2    (1100)


#define PVDF_RESULT_TICK_TA      (5) //100ms检测一次 ，10秒做离开检测
typedef struct
{
  uint16_t adc1;
  uint16_t adc2;
}pvdf_adc_info_t;
  




typedef struct
{
  uint16_t tick;
  uint16_t tickTa;
  uint8_t  ustatus;
  uint8_t  FlagStatus;
}pvdf_result_tick_info_t;
  




typedef struct
{
  uint8_t                 state;
  pvdf_result_tick_info_t tick;
}pvdf_result_info_t;
  



typedef struct
{
    pvdf_adc_info_t    adcOri;
    pvdf_result_info_t result;
}pvdf_info_t;
  
extern pvdf_info_t pvdf;;

extern void bo_pvdf_init(pvdf_info_t *pv);
extern void bo_pvdf_rule_check_update_auto(pvdf_info_t *pv,uint8_t flag);

extern void bo_pvdf_value_update(pvdf_info_t *p,uint8_t ch,int16_t adc);

extern void bo_pvdf_adc_update(pvdf_info_t *p,uint8_t flag);


extern uint8_t bo_pvdf_rule_check_result_get(pvdf_info_t *pv);

extern uint8_t bo_pvdf_somebody_onOffstate_realtime(pvdf_info_t *pv);
#ifdef __cplusplus
}
#endif

#endif 

