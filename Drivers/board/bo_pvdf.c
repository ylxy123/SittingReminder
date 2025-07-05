#include "bo_pvdf.h"


pvdf_info_t pvdf;




void bo_pvdf_value_update(pvdf_info_t *p,uint8_t ch,int16_t adc)
{
  if(ch ==0)
  {
    p->adcOri.adc1 = adc;
  }
  if(ch ==1)
  {
    p->adcOri.adc2 = adc;
  }
}
void bo_pvdf_adc_update(pvdf_info_t *p,uint8_t flag)
{
  if(flag ==1)
  {
    
    bo_pvdf_value_update(p,0,APP_AdcConvert(LL_ADC_CHANNEL_1));
    bo_pvdf_value_update(p,1,APP_AdcConvert(LL_ADC_CHANNEL_2));
    printf("\r\nsensor:[%d][%d]\r\n",p->adcOri.adc1,p->adcOri.adc2);
  }
  //printf("\r\nsensor:[%d][%d]\r\n",p->adcOri.adc1,p->adcOri.adc2);
}


void bo_pvdf_tick_restart(pvdf_info_t *pv)
{
  pv->result.tick.tick = 0;
}


uint8_t bo_pvdf_rule_check_result_get(pvdf_info_t *pv)
{
  return pv->result.state;
}

//方法1   直接采用阈值方法   样品代码 使用此方法
//方法2   通过监测突变的方法

void bo_pvdf_rule_check_update_auto(pvdf_info_t *pv,uint8_t flag)
{
  static uint8_t resultOld =0xFF;
  if(flag)
  {
    if(threadHold_u16(pv->adcOri.adc1,4095,PVDF_THREADHOLD_ADC_2) ||(threadHold_u16(pv->adcOri.adc2,0,PVDF_THREADHOLD_ADC_2)))
    {
       bo_pvdf_tick_restart(pv);
       pv->result.state  = 1;
    }
    else
    {
      if(pv->result.tick.tick < pv->result.tick.tickTa)
      {
        pv->result.tick.tick ++;
        pv->result.state  = 1;
      }
      else if(pv->result.tick.tick == pv->result.tick.tickTa)
      {
        pv->result.tick.tick ++;
         pv->result.state  = 0;
      }
      else
      {
        pv->result.state = 0;
      }
    }
    if(pv->result.state != resultOld)
    {
      printf("pv->result:[%d]\r\n",pv->result.state);
      resultOld = pv->result.state;
    }
  }
}


uint8_t bo_pvdf_somebody_onOffstate_realtime(pvdf_info_t *pv)
{
  uint8_t result =0;
  printf("adc1: %d, adc2: %d", pv->adcOri.adc1, pv->adcOri.adc2);
  if(threadHold_u16(pv->adcOri.adc2,4095,PVDF_THREADHOLD_ADC_2) ||(threadHold_u16(pv->adcOri.adc1,0,PVDF_THREADHOLD_ADC_2)))
  {
    result = 1;
  }
  else 
  {
    result = 0;
  }
  return result;
}





void bo_pvdf_init(pvdf_info_t *pv)
{
  pv->result.tick.tickTa = PVDF_RESULT_TICK_TA;
  pv->result.tick.tick  =  PVDF_RESULT_TICK_TA +1;
  
}
