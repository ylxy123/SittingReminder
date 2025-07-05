#include "core.h"
#include "string.h"
core_info_t core;
void core_init(void)
{
  core.result.tick.tickTa = CORE_SOMBODY_TICK_TA;
  core.result.tick.tick = CORE_SOMBODY_TICK_TA +1;
  
  core.mode.mode    = CORE_MODE_NORMAL;
  
  
  core.entry.tickTa = ENTRY_TICK_TA;
}



void core_somebody_check_param_reinit(core_info_t *co)
{
  co->mode.mixMode.cntOff40          = 0;
  co->mode.mixMode.cntOff50          = 0;
  co->mode.mixMode.cntOff60          = 0;
  
  co->mode.mixMode.cntOn40           = 0;
  co->mode.mixMode.cntOn50           = 0;
  co->mode.mixMode.cntOn60           = 0;
  
  
  memset(&co->mode.mixMode.cntOfflist[0],0,sizeof(co->mode.mixMode.cntOfflist));
  memset(&co->mode.mixMode.cntOnlist[0],0,sizeof(co->mode.mixMode.cntOnlist));

  co->mode.mixMode.cntSum            = 0;
    
  co->mode.mixMode.percent           = 0;
  co->entry.flag                     = 0;
  co->entry.tick                     = 0;
}

void core_sombody_check_param_continus_reinit(core_info_t *co)
{
   co->mode.mixMode.cntOffContinus  =0;
}



void core_somebody_check_list_update(core_info_t *co,uint16_t index,uint8_t status)
{
  uint16_t listIndex =0;
  listIndex = index /PVDF_ONOFF_PER_LIST_CNT_TA;
  if(listIndex <CORE_RECORD_STATE_LIST_LEN)
  {
    if(status)
    {
       co->mode.mixMode.cntOnlist[listIndex]  ++;
    }
    else 
    {
      co->mode.mixMode.cntOfflist[listIndex]  ++;
    } 
  }
}

void core_somebeody_data_rule1_update(core_info_t *co,uint8_t flag)
{
  if(flag)
  {
    co->mode.mixMode.cntOnlist[0] = co->mode.mixMode.cntOnlist[1];
    co->mode.mixMode.cntOnlist[1] = co->mode.mixMode.cntOnlist[2];
    co->mode.mixMode.cntOnlist[2] = co->mode.mixMode.cntOnlist[3];
    co->mode.mixMode.cntOnlist[3] = co->mode.mixMode.cntOnlist[4];
    co->mode.mixMode.cntOnlist[4] = co->mode.mixMode.cntOnlist[5];
    co->mode.mixMode.cntOnlist[5] = co->mode.mixMode.cntOnlist[6];;
    co->mode.mixMode.cntOnlist[6] = co->mode.mixMode.cntOnlist[7];
    co->mode.mixMode.cntOnlist[7] = co->mode.mixMode.cntOnlist[8];
    co->mode.mixMode.cntOnlist[8] = co->mode.mixMode.cntOnlist[9];
    co->mode.mixMode.cntOnlist[9] = co->mode.mixMode.cntOnlist[10];
    co->mode.mixMode.cntOnlist[10] = co->mode.mixMode.cntOnlist[11];
    co->mode.mixMode.cntOnlist[11] = 0;
    
    co->mode.mixMode.cntOfflist[0] = co->mode.mixMode.cntOfflist[1];
    co->mode.mixMode.cntOfflist[1] = co->mode.mixMode.cntOfflist[2];
    co->mode.mixMode.cntOfflist[2] = co->mode.mixMode.cntOfflist[3];
    co->mode.mixMode.cntOfflist[3] = co->mode.mixMode.cntOfflist[4];
    co->mode.mixMode.cntOfflist[4] = co->mode.mixMode.cntOfflist[5];
    co->mode.mixMode.cntOfflist[5] = co->mode.mixMode.cntOfflist[6];
    co->mode.mixMode.cntOfflist[6] = co->mode.mixMode.cntOfflist[7];
    co->mode.mixMode.cntOfflist[7] = co->mode.mixMode.cntOfflist[8];
    co->mode.mixMode.cntOfflist[8] = co->mode.mixMode.cntOfflist[9];
    co->mode.mixMode.cntOfflist[9] = co->mode.mixMode.cntOfflist[10];
    co->mode.mixMode.cntOfflist[10] = co->mode.mixMode.cntOfflist[11];
    co->mode.mixMode.cntOfflist[11] = 0;
  }
}



void core_somebeody_data_cal_update(core_info_t *co,uint8_t type,uint16_t cntSum,uint8_t flag)
{
  uint16_t index = 0;
  index = cntSum /PVDF_ONOFF_PER_LIST_CNT_TA;
  if(flag)
  {
    switch(type)
    {
      case 4:
        if(index >=8)
        {
          co->mode.mixMode.cntOn40 = 0;
          co->mode.mixMode.cntOff40 = 0;
          for(int i =0; i <8;i++)
          {
            co->mode.mixMode.cntOn40 += co->mode.mixMode.cntOnlist[index- i-1]; 
            co->mode.mixMode.cntOff40 += co->mode.mixMode.cntOfflist[index- i-1]; 
          }
        }
        break;
      case 5:
        if(index >=10)
        {
          co->mode.mixMode.cntOn50 = 0;
          co->mode.mixMode.cntOff50 = 0;
          for(int i =0; i <10;i++)
          {
            co->mode.mixMode.cntOn50 += co->mode.mixMode.cntOnlist[index- i-1]; 
            co->mode.mixMode.cntOff50 += co->mode.mixMode.cntOfflist[index- i-1]; 
          }
        }
        break;
      case 6:
         if(index >=12)
        {
          co->mode.mixMode.cntOn60 = 0;
          co->mode.mixMode.cntOff60 = 0;
          for(int i =0; i <12;i++)
          {
            co->mode.mixMode.cntOn60 += co->mode.mixMode.cntOnlist[index- i-1]; 
            co->mode.mixMode.cntOff60 += co->mode.mixMode.cntOfflist[index- i-1]; 
          }
        }
        break;
    }
  }
}


uint8_t core_somebody_shake_rule_check_update(core_info_t *co,uint8_t flag)
{
  if(flag)
  {
    co->mode.mixMode.onResult = 0;
    if(co->mode.mixMode.cntOn40 > PVDF_ONOFF_CNT_ON_L1_TA)
    {
      co->mode.mixMode.onResult =1;
    }
     if(co->mode.mixMode.cntOn50 > PVDF_ONOFF_CNT_ON_L2_TA)
    {
      co->mode.mixMode.onResult =1;
    }
     if(co->mode.mixMode.cntOn60 > PVDF_ONOFF_CNT_ON_L3_TA)
    {
      co->mode.mixMode.onResult =1;
    }
  }
  return co->mode.mixMode.onResult;
}

void core_somebody_check_update(core_info_t *co,uint8_t flag)
{
  
  uint32_t OnlistSumReg =0;
  if(flag)
  {
    if(co->entry.flag == 0 )  //周期没开始的时候 需要进行检测
    {
       if(bo_pvdf_somebody_onOffstate_realtime(&pvdf) == 1)
       {
         if(co->entry.tick < co->entry.tickTa)  //连续监测到5秒人坐在上面
         {
           co->entry.tick ++;
         }
         else
         {
           co->entry.flag = 1;   //进入监测周期
           co->entry.tick = 0;
         }
       }
       else
       {
         co->entry.flag = 0;
         co->entry.tick = 0;
       } 
       printf("entry-wait-tick[%d]TA[%d]flag[%d]\r\n",
            co->entry.tick,
            co->entry.tickTa,
            co->entry.flag);
    }
    if(co->entry.flag == 1)
    {

      if(bo_pvdf_somebody_onOffstate_realtime(&pvdf) == 1)  //如果有人
      { 
        core_somebody_check_list_update(co,co->mode.mixMode.cntSum,1);  
        co->mode.mixMode.cntOffContinus  =0 ;
      }
      else  //如果没人
      {
        core_somebody_check_list_update(co,co->mode.mixMode.cntSum,0);
        if(co->mode.mixMode.cntOffContinus < PVDF_ONOFF_CONTINUS_OFF_TA)  //在检测周期中，如果连续多少离开一段时间，则退出监测
        {
          co->mode.mixMode.cntOffContinus ++;
        }
        else 
        {
          core_somebody_check_param_reinit(co);   //参数初始化   判定人离开了座位
          core_sombody_check_param_continus_reinit(co);
        }
      }  
      co->mode.mixMode.cntSum ++; //这里不断做累加，直到判定了多少个点
      
      if(co->mode.mixMode.cntSum == 8*PVDF_ONOFF_PER_LIST_CNT_TA)
      {
         core_somebeody_data_cal_update(&core,4,co->mode.mixMode.cntSum,1);
      }
      if(co->mode.mixMode.cntSum == 9*PVDF_ONOFF_PER_LIST_CNT_TA)
      {
         core_somebeody_data_cal_update(&core,4,co->mode.mixMode.cntSum,1);
      }
      if(co->mode.mixMode.cntSum == 10*PVDF_ONOFF_PER_LIST_CNT_TA)
      {
         core_somebeody_data_cal_update(&core,4,co->mode.mixMode.cntSum,1);
         core_somebeody_data_cal_update(&core,5,co->mode.mixMode.cntSum,1);
      }
      if(co->mode.mixMode.cntSum == 11*PVDF_ONOFF_PER_LIST_CNT_TA)
      {
         core_somebeody_data_cal_update(&core,4,co->mode.mixMode.cntSum,1);
         core_somebeody_data_cal_update(&core,5,co->mode.mixMode.cntSum,1);
      }
      if(co->mode.mixMode.cntSum == 12*PVDF_ONOFF_PER_LIST_CNT_TA)
      {
        //printf("333.............\r\n");
         core_somebeody_data_cal_update(&core,4,co->mode.mixMode.cntSum,1);
         core_somebeody_data_cal_update(&core,5,co->mode.mixMode.cntSum,1);
         core_somebeody_data_cal_update(&core,6,co->mode.mixMode.cntSum,1);
      }
      
      if(core_somebody_shake_rule_check_update(&core,1)==1)
      {
        printf("already move!!!");
        LL_mDelay(1000);
        bo_motor_action_block(&motor,500,500,6,1);
        core_somebody_check_param_reinit(co);   //参数初始化   判定人离开了座位
        core_sombody_check_param_continus_reinit(co);
      }
       printf("\r\non40[%02d]off40[%02d]\r\n",
              co->mode.mixMode.cntOn40,
              co->mode.mixMode.cntOff40);
      printf("on50[%02d]off50[%02d]\r\n",
              co->mode.mixMode.cntOn50,
              co->mode.mixMode.cntOff50);
      printf("on60[%02d]off60[%02d]\r\n",
              co->mode.mixMode.cntOn60,
              co->mode.mixMode.cntOff60);     
      for(int i =0; i < CORE_RECORD_STATE_LIST_LEN;i++)
      {
          printf("[%d]on[%02d]off[%02d]\r\n",i,co->mode.mixMode.cntOnlist[i],co->mode.mixMode.cntOfflist[i]);
      }
      printf("sum[%d]continusOFF[%d]\r\n",
              co->mode.mixMode.cntSum,
              co->mode.mixMode.cntOffContinus);
        
      if(co->mode.mixMode.cntSum > CORE_RECORD_STATE_LIST_LEN*PVDF_ONOFF_PER_LIST_CNT_TA)
      {
        core_somebeody_data_rule1_update(&core,1);
        co->mode.mixMode.cntSum = (CORE_RECORD_STATE_LIST_LEN -1)*PVDF_ONOFF_PER_LIST_CNT_TA;
      }
     
//      if(co->mode.mixMode.cntSum == 72000)
//      {
//            LL_mDelay(1000);
//           bo_motor_action_block(&motor,500,500,6,1);
//           core_somebody_check_param_reinit(co);
//      }
   }
 }
    
}

void core_fsm_mode_set(core_info_t *co,uint8_t mode)
{
  co->mode.mode = mode;
}

uint8_t core_fsm_mode_get(core_info_t *co)
{
  return co->mode.mode;
}

void core_fsm_set(core_info_t *co,uint8_t state)
{
  co->fsm.state  = state;
}


void core_mode_Set(core_info_t *co,uint8_t mode)
{
  co->mode.mode  = mode;
}
uint8_t core_mode_get(core_info_t *co)
{
  return co->mode.mode;
}
  

void core_mode_update(core_info_t *co)
{
  static uint16_t cnt;
  if((LL_GPIO_ReadInputPort(GPIOA)&0x02))
  {//接了3V3 此时就不进入休眠模式
    
    cnt =0;
    core_mode_Set(co,CORE_MODE_DEBUG);
  }
  else
  {//normal模式，需要进入低功耗
    if(cnt < 3)
    {
      cnt ++;
    }
    else
    {
      core_mode_Set(co,CORE_MODE_NORMAL);
    }
  }
  
}






//void core_func_auto(core_info_t *co)
//{
//  core_mode_update(co);//判定当前处于的模式状态
//  if(core_fsm_mode_get(co) == CORE_MODE_DEBUG)
//  {
////      LL_mDelay(1000);
////      printf("debug le...\r\n");
//  }
//  else
//  {
//      //先打开定时器
//     bo_pvdf_adc_update(&pvdf,1);  //更新adc的值
//     bo_pvdf_rule_check_update_auto(&pvdf,1);  //此处判定是否有人在传感器上
//    if(bo_motor_state_get(&motor) == 1)  //motor在动作
//    {
//      //wait to end...
//    }
//    else
//    {
//      core_somebody_check_update(&core,1);   //此处判定是否要执行有人提醒
//      LL_mDelay(1000);
//      printf("enter le...\r\n");
//    }
//  } 
//}

