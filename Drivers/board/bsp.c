#include "bsp.h"


uint8_t tx[32] = "helloworld\r\n";
uint16_t tx_len =10;
__IO uint16_t AdcValue;


void bsp_init(void)
{
  dev_init();
  APP_ConfigUsart(USART1);
  printf("helloworld....\r\n");
	uart1_init();
  bo_pvdf_init(&pvdf);
  mt_lowEnergy_init();
  core_init();
  bo_motor_init();
}
