#include "stimer_event.h"
struct timer timer_100us;
struct timer timer_1ms;
struct timer timer_2ms;
struct timer timer_5ms;
struct timer timer_10ms;
struct timer timer_50ms;
struct timer timer_100ms;
struct timer timer_1000ms;

uint8_t addd =0;


uint8_t tx2[32] = "helloworld\r\n";
uint16_t tx2_len =0;

  
void dev_timer_event_init(void)
{
  timer_set(&timer_100us, 	 1);
	timer_set(&timer_1ms, 	 10);
	timer_set(&timer_2ms, 	 20);
	timer_set(&timer_5ms, 	 50);
	timer_set(&timer_10ms, 	 100);
	timer_set(&timer_50ms, 	 500);
	timer_set(&timer_100ms,  1000);
	timer_set(&timer_1000ms, 10000);
}


void dev_timer_param_reinit(void)
{
  uip_timer =0;
  timer_100us.start   = 0;
  timer_1ms.start     = 0 ;
  timer_2ms.start     = 0;
  timer_5ms.start     = 0;
  timer_10ms.start    = 0;
  timer_50ms.start    = 0;
  timer_100ms.start   = 0;
  timer_1000ms.start  = 0;
}
void dev_timer_event_update_by_timer(void)
{
	
  if(timer_expired(&timer_100us))
	{

		timer_reset(&timer_100us);
	}
  
  
	if(timer_expired(&timer_1ms))
	{
    //core_mode_update(&core);
    uart1_rx_timeout_update();
   
		timer_reset(&timer_1ms);
	}
	if(timer_expired(&timer_2ms))
	{ 
		timer_reset(&timer_2ms);
	}
	if(timer_expired(&timer_50ms))
	{ 

		timer_reset(&timer_50ms);
	}
	
	if(timer_expired(&timer_5ms))
	{ 
    bo_pvdf_adc_update(&pvdf,core_mode_get(&core) == CORE_MODE_DEBUG);  //更新adc的值
    bo_pvdf_rule_check_update_auto(&pvdf,core_mode_get(&core) == CORE_MODE_DEBUG);  //此处判定是否有人在传感器上
    bo_motor_auto(&motor);
		timer_reset(&timer_5ms);
	}
	if(timer_expired(&timer_100ms))
	{
    
   
		timer_reset(&timer_100ms);
	}
	if(timer_expired(&timer_1000ms))
	{
     core_somebody_check_update(&core,core_mode_get(&core) == CORE_MODE_DEBUG);   //此处判定是否要执行有人提醒
     printf("\r\npvdf:[%d]                     -1 somebody -0 nobody\r\n",bo_pvdf_rule_check_result_get(&pvdf));
     printf("sensor_press:[%d][%d]      -adc1 4095 -adc2 0\r\n",
            pvdf.adcOri.adc1,
            pvdf.adcOri.adc2

    );
    printf("tick_to_pvdf_0_tick:[%d]tickTa:[%d]",
            pvdf.result.tick.tick,
            pvdf.result.tick.tickTa);
		timer_reset(&timer_1000ms);
	}
}
