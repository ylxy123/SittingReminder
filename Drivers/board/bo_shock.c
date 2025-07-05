#include "bo_shock.h"

//shock_info_t boShock;
//void bo_shock_init(void)
//{
//  boShock.filter.tick.tickTa  = SHOCK_FILTER_TICK_TA; 
//  boShock.filter.tick.tick    =SHOCK_FILTER_TICK_TA +1;
//}


//void bo_shock_state_set(shock_info_t *s,uint8_t state)
//{

//  s->ori.state = state;
//  
//}

//void bo_shock_tick_rstart(shock_info_t *s,shock_tick_info_t timer)
//{
//  s->filter.tick.tick = 0;
//}

//void bo_shock_filter_state_update(shock_info_t *s)
//{
//    static uint8_t stateOld = 0xFF;
//    if(s->filter.tick.tick < s->filter.tick.tickTa)
//    {
//      s->filter.tick.tick ++;
//      s->filter.result = 1;
//    }
//    else if(s->filter.tick.tick < s->filter.tick.tickTa)
//    {
//      s->filter.tick.tick ++;
//      s->filter.result = 0;
//    }
//    else
//    {
//      s->filter.result = 0;
//    }
//    if(s->filter.result != stateOld)
//    {
//      switch(s->filter.result)
//      {
//        case 0:
//          printf("shock_sensor:[off]\r\n");
//          break;
//        case 1:
//          printf("shock_sensor:[on]\r\n");
//          break;
//      }
//      stateOld  = s->filter.result;
//  }
//}

//uint8_t bo_shock_filter_result_get(shock_info_t *s)
//{
//  return s->filter.result;
//}