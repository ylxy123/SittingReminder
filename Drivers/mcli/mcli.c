#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "mcli.h"

#define CR_CHAR '\r'
#define LF_CHAR '\n'

static const mcli_cmd_t *mcli_cmds_list[CMD_MAX_NUM];
static uint32_t mcli_cmds_num;
static mcli_if_t *mcli_if;

static const char *prompt = "$ ";



static mcli_cmd_t help_cmd = {
    .name = "help",
    .func = help_cmd_handler,
    .help = "",
};

static char mcli_read_char(void)
{
    return mcli_if->read_char();
}

static void mcli_write(const char *ch, uint32_t n)
{
    if (mcli_if == NULL)
        return;

    while (n--)
    {
        mcli_if->write_char(*ch++);
    }
}

int mcli_cmd_add(mcli_cmd_t *hdl)
{
    int i;

    for (i = 0; i < mcli_cmds_num; i++)
    {
        if (mcli_cmds_list[i] == hdl)
            return 0;
    }
    if (i >= CMD_MAX_NUM)
        return -1;

    mcli_cmds_list[mcli_cmds_num++] = hdl;
    return 0;
}

int mcli_cmd_del(mcli_cmd_t *hdl)
{
    int i;

    for (i = 0; i < mcli_cmds_num; i++)
    {
        if (mcli_cmds_list[i] == hdl)
        {
            mcli_cmds_num--;
            int remain_cmds = mcli_cmds_num - i;
            if (remain_cmds > 0)
            {
                memmove(&mcli_cmds_list[i], &mcli_cmds_list[i + 1], remain_cmds * sizeof(struct mcli_cmd_t *));
            }
            mcli_cmds_list[mcli_cmds_num] = NULL;
            return 0;
        }
    }

    return -1;
}

int mcli_cmds_add(mcli_cmd_t *hdl, uint32_t n)
{
    while (n--)
    {
        if (mcli_cmd_add(hdl++) != 0)
            return -1;
    }

    return 0;
}

int mcli_cmds_del(mcli_cmd_t *hdl, uint32_t n)
{
    while (n--)
    {
        if (mcli_cmd_del(hdl++) != 0)
            return -1;
    }

    return 0;
}

void help_cmd_handler(void)
{
    int i;
    int max_name_len = 0;

    char format[32];
    char split[] = "------------------------------------------------\r\n";

    for (i = 0; i < mcli_cmds_num; i++)
    {
        int name_len = strlen(mcli_cmds_list[i]->name);
        if (name_len > max_name_len)
        {
            max_name_len = name_len;
        }
    }
    sprintf(format, "| %%-%ds | %%s\r\n", max_name_len);

    mcli_printf("%s", split);
    mcli_printf(format, "Name", "Description");
    split[0] = '|';
    split[max_name_len + 3] = '|';
    mcli_printf("%s", split);

    for (i = 0; i < mcli_cmds_num; i++)
    {
        mcli_printf(format, mcli_cmds_list[i]->name, mcli_cmds_list[i]->help);
    }
    split[0] = '-';
    split[max_name_len + 3] = '-';
    mcli_printf("%s", split);
}

/*
return code:
argc
*/
static int mcli_args_delim(char *line, char **argv)
{
    int i;

    for (i = 0; i < CMD_ARG_MAX_NUM; i++)
    {
        if ((argv[i] = strtok(line, " ")) == NULL)
            break;
        if (i == 0)
            line = NULL;
    }

    return i;
}

static void mcli_parse(int argc, char *argv[])
{
    if (argc == 0)
        return;

    for (int i = 0; i < mcli_cmds_num; i++)
    {
        if (strcmp(argv[0], mcli_cmds_list[i]->name) == 0)
        {
            mcli_cmds_list[i]->func(argc, argv);
            return;
        }
    }

    mcli_printf("%s: command not found\r\n", argv[0]);
}

/*
return code:
<0: no line
=0: empty line
>0: command line
*/
static int mcli_getline(char ch, char *line, int size)
{
    static int i;
    int rc = -1;
    const char *echoback = "\x08 \x08";

    line[i] = ch;

    if (line[i] == LF_CHAR)
        return -1;

    if (line[i] == CR_CHAR)
    { /* end of input line */
        line[i] = '\0';
        rc = i;
        goto exit;
    }

    if ((line[i] == 0x08) || /* backspace */
        (line[i] == 0x7f))
    { /* DEL */
        if (i > 0)
        {
            i--;
            mcli_write(echoback, 3);
        }
        return -1;
    }

    if (line[i] == '\t')
        return -1;

    mcli_write(&line[i], 1);

    if (i++ >= size)
    {
        rc = -1;
        goto exit;
    }

    return -1;

exit:
    mcli_printf("\r\n");
    i = 0;
    return rc;
}

/*
return code:
<0: no line
=0: empty line
>0: command line
*/
static int rtt_mcli_getline(char *line, int size)
{
    int i = size - 1;
    int rc = -1;
    const char *echoback = "\x08 \x08";

    // if (line[i] == LF_CHAR)
    if (strchr(line, LF_CHAR))
        return -1;

    // if (line[i] == CR_CHAR)
    if (strchr(line, CR_CHAR))
    { /* end of input line */
        line[i] = '\0';
        rc = size;
        goto exit;
    }

    // if ((line[i] == 0x08) || /* backspace */
    //    (line[i] == 0x7f))
    if (strchr(line, 0x08) || strchr(line, 0x7f))
    { /* DEL */
        if (i > 0)
        {
            i--;
            mcli_write(echoback, 3);
        }
        return -1;
    }

    // if (line[i] == '\t')
    if (strchr(line, '\t'))
        return -1;

    mcli_write(line, size);

    return -1;

exit:
    mcli_printf("\r\n");
    i = 0;
    return rc;
}

void mcli_init(mcli_if_t *interface)
{
#ifndef RTT
    mcli_if = interface;
#endif
    mcli_cmd_add(&help_cmd);
}


void mcli_nput_timeout_cmd(char *cmd_buf, int16_t size)
{
  for(int i =0;i < size ;i ++)
  {
    mcli_input_char(cmd_buf[i]);
  }
}

void mcli_input_char(char ch)
{
    char *argv[CMD_ARG_MAX_NUM];
    static char cmd_buf[CMD_BUF_SIZE];

    if (mcli_getline(ch, cmd_buf, CMD_BUF_SIZE) >= 0)
    {
        mcli_parse(mcli_args_delim(cmd_buf, argv), argv);
        mcli_write(prompt, 2);
    }
}

void rtt_mcli_input(char *cmd_buf, int16_t size)
{
    char *argv[CMD_ARG_MAX_NUM];
    if (rtt_mcli_getline(cmd_buf, size) >= 0)
    {
        mcli_parse(mcli_args_delim(cmd_buf, argv), argv);
        mcli_write(prompt, 2);
    }
}

void mcli_loop_run(void)
{
#ifdef RTOS
    mcli_write(prompt, 2);
    while (1)
    {
#ifndef RTT
        mcli_input_char(mcli_read_char());
#else
        char cmd_buf[CMD_BUF_SIZE];
        int rtt_len = SEGGER_RTT_Read(0, cmd_buf, sizeof(cmd_buf));
        if (rtt_len)
        {
            rtt_mcli_input(cmd_buf, rtt_len);
        }
#endif
    }
#else
#ifndef RTT
    mcli_input_char(mcli_read_char());
#else
    static char cmd_buf[CMD_BUF_SIZE];
    int rtt_len = SEGGER_RTT_Read(0, cmd_buf, sizeof(cmd_buf));
    if (rtt_len)
    {
        rtt_mcli_input(cmd_buf, rtt_len);
    }
#endif
#endif
}

void mcli_putc(char ch)
{
    mcli_if->write_char(ch);
}

#ifndef RTT
int mcli_printf(const char *format, ...)
{

    static char printbuf[256];
    va_list ap;

    va_start(ap, format);
    int n = vsnprintf(printbuf, sizeof(printbuf), format, ap);
    va_end(ap);

    if (n > 0)
        mcli_write(printbuf, n);

    return n;
}
#endif
