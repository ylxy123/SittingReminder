#include "bo_motor.h"

motor_info_t motor;

void bo_motor_gpio_init(void)
{
    LL_AHB1_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_5, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_5, LL_GPIO_SPEED_FREQ_VERY_HIGH);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_5, LL_GPIO_PULL_UP);
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_5, LL_GPIO_AF_5);
}
void TIM14_Init(void)
{

    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM14);

    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    TIM_InitStruct.Prescaler = 23;      
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 999;    
    TIM_InitStruct.ClockDivision = 0;
    LL_TIM_Init(TIM14, &TIM_InitStruct);

    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.CompareValue = 999; 
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
    LL_TIM_OC_Init(TIM14,LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

    LL_TIM_EnableCounter(TIM14);
}

void tm_motor_pwm_set(motor_info_t *m,uint8_t percent)
{
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
  if(percent != m->pwm.percent)
  {
   if(percent <= 100)
   {
      m->pwm.percent = percent;
      TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
      TIM_OC_InitStruct.CompareValue = percent * 10;
      TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
      TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
      LL_TIM_OC_Init(TIM14,LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);

      LL_TIM_EnableCounter(TIM14);
     
    }
   
  }
}




void bo_motor_mode_set(motor_info_t *m,uint8_t mode,...)
{
  va_list ap;
  va_start(ap,mode);
  if(mode == MOTOR_MODE_BLINK)
  {
    m->mode.param.tickOnTa  = va_arg(ap,int);
    m->mode.param.tickOffTa = va_arg(ap,int);
    m->mode.param.pwmDuty   = va_arg(ap,int);
    m->mode.param.cntTa     = va_arg(ap,int);
  }
  va_end(ap);
  m->mode.mode = mode;
  m->mode.param.tick = 0;
  m->mode.param.cnt  = 0;
  m->mode.actionFlag = 1;
}


uint8_t bo_motor_state_get(motor_info_t *m)
{
  return m->mode.actionFlag;
}



void bo_motor_action_block(motor_info_t *m,uint16_t highTime,uint16_t lowTime,uint16_t cnt,uint8_t flag)
{
  if(flag)
  {
   
    bo_motor_init();
    for(int i = 0;i < cnt;i++)
    {
      power_5V_on();
//      tm_motor_pwm_set(m,50);
      LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_5);
      LL_mDelay(highTime);
      //power_5V_off();
//      tm_motor_pwm_set(m,0);
      LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_5);
      LL_mDelay(lowTime);
    }
    power_5V_off();
//    tm_motor_pwm_set(m,0);
    LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_5);
  }
  
}


void bo_motor_auto(motor_info_t *m)
{
  if(m->mode.mode == MOTOR_MODE_OFF)
  {//此处将pwm设置为0
    tm_motor_pwm_set(m,0);
    power_5V_off();
  }
  else if(m->mode.mode == MOTOR_MODE_ON)
  {
    power_5V_on();
    tm_motor_pwm_set(0,50);
  }
  else if(m->mode.mode == MOTOR_MODE_BLINK) //
  {
    //m->mode.actionFlag = 1;
    if(m->mode.param.tick < m->mode.param.tickOnTa)
    {
       power_5V_on();
      m->mode.param.tick ++;
      power_5V_on();
      tm_motor_pwm_set(m,m->mode.param.pwmDuty);
    }
    else if(m->mode.param.tick <  (m->mode.param.tickOnTa + m->mode.param.tickOffTa))
    {
      m->mode.param.tick ++;
      tm_motor_pwm_set(m,0);
    }
    else
    {
      
      if(m->mode.param.cnt < m->mode.param.cntTa)
      {
        m->mode.param.cnt ++;
        printf("morot-cnt[%d]\r\n",m->mode.param.cnt);

        m->mode.param.tick = 0;
      }
      else if(m->mode.param.cnt == m->mode.param.cntTa)
      {
        m->mode.param.cnt ++;
        printf("morot-END\r\n");
        tm_motor_pwm_set(m,0); //此处结束了
        m->mode.actionFlag = 0;
        power_5V_off();
      }
      else
      {
        tm_motor_pwm_set(m,0); //此处结束了
        m->mode.actionFlag = 0;
        power_5V_off();
       
      }
    }
  }
}











void bo_motor_init2(void)
{
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  LL_GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT; 
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_5);
  
}

void bo_motor_init(void)
{
  dev_gpio_init();
  //bo_motor_gpio_init();
  //TIM14_Init();
 // dev_gpio_init();
  bo_motor_init2();
}

void bo_motor_deinit(void)
{
  
}


