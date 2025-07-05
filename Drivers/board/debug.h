#ifndef __DEBUG_H
#define __DEBUG_H

#include "stdint.h"
#include "dev.h"

#include "bsp.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
  uint8_t mode;
}debug_mode_info_t;


typedef struct
{
  debug_mode_info_t level;
}debug_info_t;

extern debug_info_t debug;



#ifdef __cplusplus
}
#endif

#endif 

