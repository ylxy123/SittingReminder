#include "th_rule_check.h"

uint8_t threadHold_u16(uint16_t a,uint16_t b,uint16_t threadHold)
{
  uint8_t tResult = 0;
  if(a > b)
  {
    if((a-b ) >threadHold)
    {
      tResult = 1;
    }
    else 
    {
      tResult = 0;
    }
  }
  else 
  {
    if((b -a ) > threadHold)
    {
      tResult = 1;
    }
    else
    {
      tResult = 0;
    }
  }
  return tResult;
}