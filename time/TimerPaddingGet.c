#include                "libFireBird.h"

bool TimerPaddingGet(short *PrePaddingMin, short *PostPaddingMin)
{
  TRACEENTER;

  bool ret = FALSE;

  if(TimerPaddingAPICheck())
  {
    if(PrePaddingMin) *PrePaddingMin = TAP_GetSystemVar(SYSVAR_RecPaddingFore);
    if(PostPaddingMin) *PostPaddingMin = TAP_GetSystemVar(SYSVAR_RecPaddingRear);
    ret = TRUE;
  }
  else
  {
    byte                 *EEPROM;

    EEPROM = (byte*)FIS_vEEPROM();
    if(!EEPROM)
    {
      if(PrePaddingMin) *PrePaddingMin = 0;
      if(PostPaddingMin) *PostPaddingMin = 0;
    }
    else
    {
      if(PrePaddingMin) *PrePaddingMin  = EEPROM[0x21] & 0x1f;
      if(PostPaddingMin) *PostPaddingMin  = EEPROM[0x22] & 0x1f;
      ret = TRUE;
    }
  }

  TRACEEXIT;
  return ret;
}
