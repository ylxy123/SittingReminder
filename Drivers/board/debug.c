#include "debug.h"


debug_info_t debug;


void debug_list_printf(debug_info_t *debug)
{
  if(debug->level.mode == 1)
  {
    printf("sensor-pressure:ADC[%d][%d]\r\n",  
            pvdf.adcOri.adc1,
            pvdf.adcOri.adc2);
  }
}