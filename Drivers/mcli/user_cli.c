/**
 *
 * @file user_cli.c
 * @author Javen
 * @date 2024/12/07 10:48:39
 * @version 0.1
 * @note cli命令初始化相关的一些操作
 * @since
 * @attention
 *
 */

#define _USER_CLI_GLOBALE__
//#include "include.h"
#include "mcli.h"
#include "user_cli.h"
#ifndef RTT
static void cli_write_char(char ch)
{
    // mhal_uart_write(UART0, &ch, 1);//适配自己的串口发送单字节API
      
    /* transmit data */
  LL_USART_TransmitData8(USART1, ch);
  while(LL_USART_IsActiveFlag_TXE(USART1) != 1);
}

static char cli_read_char(void)
{
    char ch = 0;
//    char n = 1;
    // mhal_uart_read(UART0, &ch, &n, MOS_WAIT_FOREVER);//适配自己的串口读取单字节API
    return ch;
}

// 指定串口读写函数
static mcli_if_t mcli_if = {
    .write_char = cli_write_char,
    .read_char = cli_read_char,
};
#endif



void tm_mcli_core_mode_set(int argc, char *argv[])
{
   
}

void tm_mcli_motor_interface(int argc, char *argv[])
{
   if(memcmp((char *)argv[1],"set",strlen("set")) == 0)
   {
      if(memcmp((char *)argv[2],"periodTick",strlen("periodTick")) == 0)
      {
        core.result.tick.tickTa = (uint16_t )atoi((char *)argv[3]);
        printf("motor periodTick[%d]\r\n",core.result.tick.tickTa );
      }
   }
}

void tm_mcli_sensor_state(int argc, char *argv[])
{
   
}


void tm_mcli_motor_interface2(int argc, char *argv[])
{
  uint16_t tickON;
  uint16_t tickOff;
  uint8_t percent;
  uint16_t cntTa;
  //if(argc ==6)
   {
     printf("tm_mcli_motor_interface2\r\n");
     printf("[%s]\r\n",argv[1]);
    if(memcmp((char *)argv[1],"blink",strlen("blink")) == 0)
    {
      tickON  =  (uint16_t)atoi(argv[2]);
      tickOff =  (uint16_t)atoi(argv[3]);
      percent =  (uint8_t)atoi(argv[4]);
      cntTa   =  (uint16_t)atoi(argv[5]);
      printf("[%d][%d][%d][%d]\r\n",tickON,tickOff,percent,cntTa);
      bo_motor_mode_set(&motor,MOTOR_MODE_BLINK,tickON,tickOff,percent,cntTa);
    }
    else  if(memcmp((char *)argv[1],"on",strlen("on")) == 0)
    {
      bo_motor_mode_set(&motor,MOTOR_MODE_ON);
    }
    else  if(memcmp((char *)argv[1],"off",strlen("off")) == 0)
    {
      bo_motor_mode_set(&motor,MOTOR_MODE_OFF);
    }
   }
//   else
//   {
//     printf("param_num_is_err[%d]\r\n",argc);
//   }
}



void tm_mcli_log_interface(int argc, char *argv[])
{
  if(memcmp((char *)argv[1],"L1",strlen("L1")) == 0)
  {
    debug.level.mode = 1;
  }
  else if(memcmp((char *)argv[1],"L2",strlen("L2")) == 0)
  {
    debug.level.mode = 2;
  }
  else if(memcmp((char *)argv[1],"L3",strlen("L3")) == 0)
  {
    debug.level.mode = 3;
  }
  else
  {
    debug.level.mode = 0;
  }
}



// 自定义命令，最大CMD_MAX_NUM条
static const mcli_cmd_t my_cmds[] = {
    {"coreMode", "interface-[auto]/[manual]",  tm_mcli_core_mode_set},
    {"motor",    "interface-[set periodTic $periocTick]/[set pwmDuty $pwmDuty]", tm_mcli_motor_interface},
    {"sensor",   "interface-[update on]/[update off]/[update once]",tm_mcli_sensor_state},
    {"motor2",   "interface-[set  ...]valist", tm_mcli_motor_interface2},
    {"log",      "interface-[L1][L2][L3]", tm_mcli_log_interface}
};

/**
 *
 * @brief 初始化cli,并添加自定义的指令
 * @author Javen
 * @date 2024/12/07 09:52:20
 * @version 0.1
 * @note 注解，可以是详细的注解
 * @remarks   备注事项
 * @attention 注意事项
 * @param a 参数a说明
 * @return 返回结果说明
 *
 */
void user_cli_cmds_init(void)
{
#ifdef RTT
    mcli_init(NULL); // 使用SEGGER_RTT时不需要制定串口读写入口
#else
    mcli_init(&mcli_if);
#endif
    mcli_cmds_add((mcli_cmd_t *)my_cmds, sizeof(my_cmds) / sizeof(mcli_cmd_t));
}
