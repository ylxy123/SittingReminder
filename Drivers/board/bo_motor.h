#ifndef __BO_MOTOR_H
#define __BO_MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"
#include "dev.h"
#include "main.h"
#include "stdarg.h"



//enum
//{
//  MOTOR_FSM_STATE_IDLE,
//  MOTOR_FSM_STATE_MANUAL_ENTRY,
//  MOTOR_FSM_STATE_MANUAL_INIT,
//  MOTOR_FSM_STATE_MANUAL_KEEP,
//  
//  
//  MOTOR_FSM_STATE_AUTO_ENTRY,  //入口
//  MOTOR_FSM_STATE_AUTO_INIT,   //初始化
//  MOTOR_FSM_STATE_AUTO_WAIT,                        //等待初始化完成
//  //MOTOR_FSM_sTATE_AUTO_SENSOR_PRESSURE_GET_UPDATE,  //压电膜 数据更新 周期性更新2ms
//  MOTOR_FSM_STATE_AUTO_RESULT_RULE_CHECK,    //     //此处进行规则检测
//  
//  MOTOR_FSM_STATE_AUTO_REUSLT_ACTION_MOTOR,
//  MOTOR_FSM_STATE_AUTO_RESULT_ACITON_KEEP,
//  MOTOR_FSM_STATE_AUTO_RESULT_ACTION_RESTART,
//  MOTOR_FSM_STATE_AUTO_RESULT_ERR,
//  
//  MOTOR_FSM_STATE_END

//};

#define MOTOR_MODE_OFF     (1)
#define MOTOR_MODE_ON      (2)
#define MOTOR_MODE_BLINK   (3)

#define MOTOR_TICK_INTERVAL  (5)
typedef struct
{
  uint16_t tick;
  uint16_t tickOnTa;
  uint16_t tickOffTa;
  uint16_t tickTa;
  uint16_t pwmDuty;
  uint16_t cnt;
  uint16_t cntTa;
}motor_mode_param_info_t;



typedef struct
{
  uint8_t                 mode;
  motor_mode_param_info_t param; 
  uint8_t                 actionFlag ;//在blink条件下他代表了执行结束
}motor_mode_info_t;


typedef struct
{
   uint8_t state;
}motor_fsm_info_t;

typedef struct
{
   uint8_t percent;
}motor_pwm_info_t;


typedef struct
{
  motor_fsm_info_t  fsm;
  motor_mode_info_t mode;
  motor_pwm_info_t  pwm;
}motor_info_t;
extern motor_info_t motor;;
  
extern void bo_motor_mode_set(motor_info_t *m,uint8_t mode,...);
extern void bo_motor_auto(motor_info_t *m);

extern void bo_motor_init(void);
extern void tm_motor_pwm_set(motor_info_t *m,uint8_t percent);

extern uint8_t bo_motor_state_get(motor_info_t *m);

extern void bo_motor_action_block(motor_info_t *m,uint16_t highTime,uint16_t lowTime,uint16_t cnt,uint8_t flag);
#ifdef __cplusplus
}
#endif

#endif 

