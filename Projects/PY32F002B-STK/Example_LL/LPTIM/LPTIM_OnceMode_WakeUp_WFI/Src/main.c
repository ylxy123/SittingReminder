/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "py32f002bxx_ll_Start_Kit.h"


int main(void)
{
  uint32_t cnt =0;
  bsp_init();
  LL_mDelay(6000);
  bo_pvdf_adc_update(&pvdf,1);  //更新adc的值
  if(bo_pvdf_somebody_onOffstate_realtime(&pvdf) == 1)
  {
      bo_motor_action_block(&motor,500,500,2,1);
  }
  else
  {
      bo_motor_action_block(&motor,500,500,1,1);
  }
  while (1)
  {

    LL_LPTIM_Disable(LPTIM);//低功耗定时器
    mt_lowEnergy_wakeup_delay();  //低功耗启动延时
    APP_ConfigUsart(USART1);    //初始化串口
    printf("Tick-[%d]\r\n",cnt++);
   // LL_mDelay(3000);
    bo_pvdf_adc_update(&pvdf,1);  //更新adc的值
    bo_pvdf_rule_check_update_auto(&pvdf,1);  //此处判定是否有人在传感器上
    core_somebody_check_update(&core,1);   //此处判定是否要执行有人提醒
//    printf("adc1[%d]adc2[%d]\r\n",pvdf.adcOri.adc1,pvdf.adcOri.adc2);
//   
    //printf("\r\npvdf:[%d]                     -1 somebody -0 nobody\r\n",bo_pvdf_rule_check_result_get(&pvdf));
    printf("sensor_press:[%d][%d]\r\n",
           pvdf.adcOri.adc1,
            pvdf.adcOri.adc2

    );

    mt_lowEnergy_enterStop(); //修改测试周期

  }
}
