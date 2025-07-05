#ifndef __core_H
#define __core_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"
#include "dev.h"
#include "main.h"



#define CORE_MODE_AUTO     (1)
#define CORE_MODE_MANUAL   (2)



#define CORE_SOMBODY_TICK_TA     (10)

enum
{
  CORE_STATE_IDEL,
  
  CORE_STATE_LE_WAKEUP_ENTRY,    // 唤醒在这里
  CORE_STATE_LE_WAKEUP_INIT,     //进行各类初始化
  CORE_STATE_LE_WAKEUP_MODE,     //debug模式和normal模式在这里进行选择
  CORE_STATE_LE_WAKEUP_GET,      //adc的获取
//  CORE_STATE_LE_WAKEUP_WAIT,   //等待10ms的时间，每一次均需要等待10ms
  CORE_STATE_LE_TIP_ACTION,      //提醒的动作在这里执行
  CORE_STATE_LE_TIP_ACTION_KEEP, //如果出现tip的动作，在之类进行结束检测
  CORE_STATE_LE_WAKEUP_DEINIT,   //进行反初始化准备

  
  
  CORE_STATE_NORMAL_ENTRY,        //此处进行初始化
  CORE_STATe_NORMAL_INIT,         //进行UART的初始化
  CORE_STATE_NORMAL_MODE,         //此处进行mode的切换判定
  CORE_STATE_NORMAL_DEINIT,
  
  
  CORE_STATE_LE_ENTRY,
  CORE_STATE_END
};




typedef struct
{
  uint16_t tick;
  uint16_t tickTa;
  uint8_t  flag;
  uint8_t  ustatus;
}core_tick_info_t;




typedef struct
{
  uint8_t state;
}core_fsm_info_t;



#define CORE_MODE_NORMAL   (1)
#define CORE_MODE_DEBUG    (2)



#define CORE_RECORD_STATE_LIST_LEN   (12)   //记录几组数据
#define PVDF_ONOFF_PER_LIST_CNT_TA   (150)  //每组数据记录的长度
#define PVDF_ONOFF_CNT_MAX_TA        (CORE_RECORD_STATE_LIST_LEN *PVDF_ONOFF_PER_LIST_CNT_TA)  //记录的最大长度
#define PVDF_ONOFF_CONTINUS_OFF_TA   (150)  //检测人离开的 连续点长度


#define PVDF_ONOFF_CNT_L1_TA        (8*PVDF_ONOFF_PER_LIST_CNT_TA)  //40分钟
#define PVDF_ONOFF_CNT_L2_TA        (9*PVDF_ONOFF_PER_LIST_CNT_TA)  //45分钟
#define PVDF_ONOFF_CNT_L3_TA        (10*PVDF_ONOFF_PER_LIST_CNT_TA)  //50分钟
#define PVDF_ONOFF_CNT_L4_TA        (11*PVDF_ONOFF_PER_LIST_CNT_TA)  //55分钟
#define PVDF_ONOFF_CNT_L5_TA        (12*PVDF_ONOFF_PER_LIST_CNT_TA)  //60分钟



#define PVDF_ONOFF_CNT_ON_L1_TA     (1140)  //38分钟
#define PVDF_ONOFF_CNT_ON_L2_TA     (1350)  //45分钟
#define PVDF_ONOFF_CNT_ON_L3_TA     (1500)  //50分钟


typedef struct
{
  uint32_t cntOn40;
  uint32_t cntOff40;
  
  uint32_t cntOn50;
  uint32_t cntOff50;
  
  uint32_t cntOn60;
  uint32_t cntOff60;
  
  uint8_t onResult;
  
  uint32_t cntOnlist[CORE_RECORD_STATE_LIST_LEN];
  uint32_t cntOfflist[CORE_RECORD_STATE_LIST_LEN];
  
  uint16_t cntListIndex;
  
  uint16_t cntOffContinus;// 人离开连续的点
  float    percent;
  uint32_t cntSum;
  
 
}core_mixmode_param_info_t;


//60*60
//#define PVDF_ONOFF_CNT_MAX_TA       (3600)
//#define PVDF_ONOFF_CNT_BASE_TA      (1800)
//#define PVDF_ONOFF_CNT_STEP_TA      (180)
//#define PVDF_ONOFF_CNT_SETP_NUM_TA  (10)


//#define PVDF_ONOFF_BASE_PERCENT     (90)
//#define PVDF_ONOFF_STEP_PERCENT     (3)


//#define PVDF_ONOFF_CONTINUS_OFF_TA   (180)


//#define PVDF_ONOFF_CNT_MAX_TA       (360)
//#define PVDF_ONOFF_CNT_BASE_TA      (180)
//#define PVDF_ONOFF_CNT_STEP_TA      (18)
//#define PVDF_ONOFF_CNT_SETP_NUM_TA  (10)


//#define PVDF_ONOFF_BASE_PERCENT     (90)
//#define PVDF_ONOFF_STEP_PERCENT     (3)


//#define PVDF_ONOFF_CONTINUS_OFF_TA   (18)


//#define PVDF_ONOFF_CNT_MAX_TA       (120*60)
//#define PVDF_ONOFF_CNT_L1_TA        (40*60)
//#define PVDF_ONOFF_CNT_L2_TA        (50*60)
//#define PVDF_ONOFF_CNT_L3_TA        (60*60)
//#define PVDF_ONOFF_CNT_L4_TA        (70*60)
//#define PVDF_ONOFF_CNT_L5_TA        (80*60)
//#define PVDF_ONOFF_CNT_L6_TA        (90*60)
//#define PVDF_ONOFF_CNT_L7_TA        (100*60)
//#define PVDF_ONOFF_CNT_L8_TA        (110*60)
//#define PVDF_ONOFF_CNT_L9_TA        (120*60)



//#define PVDF_ONOFF_CNT_ON_L1_TA     (2280)  //38分钟
//#define PVDF_ONOFF_CNT_ON_L2_TA     (2700)  //45分钟
//#define PVDF_ONOFF_CNT_ON_L3_TA     (3000)  //50分钟
//#define PVDF_ONOFF_CNT_ON_L4_TA     (3360)  //56分钟
//#define PVDF_ONOFF_CNT_ON_L5_TA     (3744)  //62分24秒
//#define PVDF_ONOFF_CNT_ON_L6_TA     (4104)  //68分24秒
//#define PVDF_ONOFF_CNT_ON_L7_TA     (4440)  //74分
//#define PVDF_ONOFF_CNT_ON_L8_TA     (4752)  //79分12秒
//#define PVDF_ONOFF_CNT_ON_L9_TA     (5040)  //84分钟

//#define PVDF_ONOFF_CONTINUS_OFF_TA   (600)


//#define PVDF_ONOFF_CNT_MAX_TA       (120*6)
//#define PVDF_ONOFF_CNT_L1_TA        (40*6)
//#define PVDF_ONOFF_CNT_L2_TA        (50*6)
//#define PVDF_ONOFF_CNT_L3_TA        (60*6)
//#define PVDF_ONOFF_CNT_L4_TA        (70*6)
//#define PVDF_ONOFF_CNT_L5_TA        (80*6)
//#define PVDF_ONOFF_CNT_L6_TA        (90*6)
//#define PVDF_ONOFF_CNT_L7_TA        (100*6)
//#define PVDF_ONOFF_CNT_L8_TA        (110*6)
//#define PVDF_ONOFF_CNT_L9_TA        (120*6)



//#define PVDF_ONOFF_CNT_ON_L1_TA     (228)  //38分钟
//#define PVDF_ONOFF_CNT_ON_L2_TA     (270)  //45分钟
//#define PVDF_ONOFF_CNT_ON_L3_TA     (300)  //50分钟
//#define PVDF_ONOFF_CNT_ON_L4_TA     (336)  //56分钟
//#define PVDF_ONOFF_CNT_ON_L5_TA     (374)  //62分24秒
//#define PVDF_ONOFF_CNT_ON_L6_TA     (410)  //68分24秒
//#define PVDF_ONOFF_CNT_ON_L7_TA     (444)  //74分
//#define PVDF_ONOFF_CNT_ON_L8_TA     (475)  //79分12秒
//#define PVDF_ONOFF_CNT_ON_L9_TA     (504)  //84分钟



typedef struct
{
  uint8_t mode;
  core_mixmode_param_info_t mixMode;
  uint8_t shakeflag;
}core_mode_info_t;



typedef struct
{
  uint8_t          someBody;
  core_tick_info_t tick;
}core_result_info_t;


#define  ENTRY_TICK_TA  (5)
typedef struct
{
  uint16_t tick;
  uint16_t tickTa;
  uint8_t  flag;
}core_entry_info_t;

typedef struct
{ 
  core_fsm_info_t    fsm;
  core_mode_info_t   mode;
  core_result_info_t result;
  core_entry_info_t  entry;
}core_info_t;

extern core_info_t core;;


extern void core_init(void);
extern void core_fsm_auto(core_info_t *co);
extern void core_fsm_set(core_info_t *co,uint8_t state);


extern void core_mode_update(core_info_t *co);


extern uint8_t core_mode_get(core_info_t *co);


extern void core_somebody_check_update(core_info_t *co,uint8_t flag);
extern void core_func_auto(core_info_t *co);



#ifdef __cplusplus
}
#endif

#endif 

