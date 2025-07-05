#ifndef __LOW_ENERGY_H
#define __LOW_ENERGY_H

#include "stdint.h"
#include "dev.h" 

#include "bsp.h"


#ifdef __cplusplus
extern "C" {
#endif


extern  void mt_lowEnergy_init(void);
extern void mt_lowEnergy_wakeup_delay(void);
extern  void APP_EnterStop(void);
extern void mt_lowEnergy_enterStop(void);

#ifdef __cplusplus
}
#endif

#endif 

