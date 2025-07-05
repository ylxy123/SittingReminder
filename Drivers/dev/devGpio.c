#include "devGpio.h"


void dev_gpio_init(void)
{
  
  //PA01 3V3
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	LL_GPIO_InitTypeDef GPIO_InitStruct_A;
  GPIO_InitStruct_A.Pin = LL_GPIO_PIN_1;
  GPIO_InitStruct_A.Mode = LL_GPIO_MODE_INPUT; 
  GPIO_InitStruct_A.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct_A.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct_A);

  
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin =  LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);

  //LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
}


void dev_gpio_le_mode(void)
{
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
	LL_GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT; 
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}



void power_5V_off(void)
{
  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
}

void power_5V_on(void)
{
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
}