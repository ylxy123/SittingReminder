#include "lowenergy.h"
 
 /* Private define ------------------------------------------------------------*/
#define Delay             120*3
/* Private variables ---------------------------------------------------------*/
LL_LPTIM_InitTypeDef LPTIM_InitStruct = {0};
__IO uint32_t RatioNops = 0;
 


void APP_LptimIRQCallback(void)
{
  if((LL_LPTIM_IsActiveFlag_ARRM(LPTIM) == 1) && (LL_LPTIM_IsEnabledIT_ARRM(LPTIM) == 1))
  {   
    LL_LPTIM_ClearFLAG_ARRM(LPTIM);
  }
}


static void APP_ConfigLptimClock(void)
{
  LL_RCC_LSI_Enable();
  while(LL_RCC_LSI_IsReady() != 1)
  {
  }
  LL_RCC_SetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE_LSI);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPTIM1);
}


static void APP_ConfigLptim(void)
{   
  NVIC_SetPriority(LPTIM1_IRQn, 0);
  NVIC_EnableIRQ(LPTIM1_IRQn);
  LL_LPTIM_EnableIT_ARRM(LPTIM);
}

void mt_board_deinit_all(void)
{
  mt_uart_deinit(USART1);
  dev_gpio_le_mode();
}

 void APP_EnterStop(void)
{
  
  mt_board_deinit_all();
  
  
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  LL_PWR_SetLprMode(LL_PWR_LPR_MODE_LPR);
  LL_PWR_SetStopModeSramVoltCtrl(LL_PWR_SRAM_RETENTION_VOLT_CTRL_LDO);
  LL_LPM_EnableDeepSleep();
  __WFI();
  LL_LPM_EnableSleep();
}

void mt_lowEnergy_enterStop(void)
{ 
  //printf("enter\r\n");
  LL_LPTIM_Enable(LPTIM);
  LL_LPTIM_SetAutoReload(LPTIM, 507); //约需要2S唤醒一次
 //LL_LPTIM_SetAutoReload(LPTIM, 60); //约需要0.2S唤醒一次
  LL_LPTIM_StartCounter(LPTIM, LL_LPTIM_OPERATING_MODE_ONESHOT);
  APP_EnterStop();
}

void mt_lowEnergy_wakeup_delay(void)
{
  RatioNops = Delay * (SystemCoreClock / 1000000U) / 4;  
}

void mt_lowEnergy_init(void)
{
   
  LL_EXTI_EnableIT(LL_EXTI_LINE_29);   /* Enable EXTI Line 29 interrupt wakeup */
  LL_EXTI_DisableEvent(LL_EXTI_LINE_29); /* Disable EXTI Line 29 event wakeup */
  APP_ConfigLptimClock();
  APP_ConfigLptim();
  LPTIM_InitStruct.Prescaler = LL_LPTIM_PRESCALER_DIV128;        /* prescaler: 128 */
  LPTIM_InitStruct.UpdateMode = LL_LPTIM_UPDATE_MODE_IMMEDIATE;  /* registers are updated after each APB bus write access */
  if (LL_LPTIM_Init(LPTIM, &LPTIM_InitStruct) != SUCCESS)
  {
    
  }
}
