#include "devTim.h"


void APP_ConfigTIM1(void)
{
  /* Configure TIM1 */
  LL_TIM_InitTypeDef TIM1CountInit = {0};

  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;/* tDTS=tCK_IN                      */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;    /* Counter used as upcounter        */
  TIM1CountInit.Prescaler           = 8-1;                   /* clock prescaler:8000            */
  TIM1CountInit.Autoreload          = 300-1;                   /* Autoreload value:3000           */
  TIM1CountInit.RepetitionCounter   = 0;                        /* Repetition counter value:0      */

  /* Initialize TIM1*/
  LL_TIM_Init(TIM1,&TIM1CountInit);

  /* Clear the update interrupt flag (UIF).  */
  LL_TIM_ClearFlag_UPDATE(TIM1);

  /*Enable update interrupt (UIE) */
  LL_TIM_EnableIT_UPDATE(TIM1);

  /*Enable TIM1 */
  LL_TIM_EnableCounter(TIM1);

  /*Enable UPDATE interrupt */
  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,0);
}


void dev_tim_init(void)
{
	APP_ConfigTIM1();
}

