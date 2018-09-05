#include                "libFireBird.h"

bool TimerPaddingSet(short *PrePaddingMin, short *PostPaddingMin)
{
  TRACEENTER;

  bool ret = FALSE;

  if(TimerPaddingAPICheck())
  {
    if(PrePaddingMin) TAP_SetSystemVar(SYSVAR_RecPaddingFore, *PrePaddingMin);
    if(PostPaddingMin) TAP_SetSystemVar(SYSVAR_RecPaddingRear, *PostPaddingMin);
    ret = TRUE;
  }
  else
  {
    byte                 *EEPROM;

    EEPROM = (byte*)FIS_vEEPROM();
    if(EEPROM)
    {
      if(PrePaddingMin) EEPROM[0x21] = (EEPROM[0x21] & 0xe0) | (*PrePaddingMin & 0x1f);
      if(PostPaddingMin) EEPROM[0x22] = (EEPROM[0x22] & 0xe0) | (*PostPaddingMin & 0x1f);
      ret = TRUE;
    }
  }

  TRACEEXIT;
  return ret;
}
