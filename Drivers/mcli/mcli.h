#ifndef _MCLI_H
#define _MCLI_H

#include <stdint.h>
//#define RTOS //是否使用os系统
//#define RTT // 是否使用SEGGER_RTT打印和输入

#ifdef RTT
#include "SEGGER_RTT.h"
#define mcli_printf(format, ...) SEGGER_RTT_printf(0, format, ##__VA_ARGS__)
#endif

#define CMD_MAX_NUM 10     // 最大自定义指令条数
#define CMD_ARG_MAX_NUM 10 // 单条指令最大参数数量
#define CMD_BUF_SIZE 128   // 单条指令最大字节数

typedef struct
{
    void (*write_char)(char ch);
    char (*read_char)(void);
} mcli_if_t;

typedef struct
{
    const char *name;                     // 指令名称
    const char *help;                     // 帮助信息
    void (*func)(int argc, char *argv[]); // 回调函数
} mcli_cmd_t;

void mcli_init(mcli_if_t *interface); // 初始化
void mcli_loop_run(void);             // 主线程
int mcli_cmd_add(mcli_cmd_t *hdl);
int mcli_cmd_del(mcli_cmd_t *hdl);
int mcli_cmds_add(mcli_cmd_t *hdl, uint32_t n);
int mcli_cmds_del(mcli_cmd_t *hdl, uint32_t n);

extern void help_cmd_handler(void);
extern void mcli_nput_timeout_cmd(char *cmd_buf, int16_t size);
void mcli_putc(char ch);
#ifndef RTT
int mcli_printf(const char *format, ...);
#endif
void mcli_input_char(char ch);

#endif
