#ifndef __USER_CLI__
#define __USER_CLI__

#include "mcli.h"
#include "dev.h"
#include "string.h"

#include "bsp.h"


#ifdef _USER_CLI_GLOBALE__
#define _EXT_USER_CLI__
#else
#define _EXT_USER_CLI__ extern
#endif
void user_cli_cmds_init(void);
#endif
