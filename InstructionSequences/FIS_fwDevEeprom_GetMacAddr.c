#include "../libFireBird.h"

inline dword FIS_fwDevEeprom_GetMacAddr(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwDevEeprom_GetMacAddr");
  #endif

  static dword          fwDevEeprom_GetMacAddr = 0;

  if(!fwDevEeprom_GetMacAddr)
    fwDevEeprom_GetMacAddr = TryResolve("DevEeprom_GetMacAddr");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwDevEeprom_GetMacAddr;
}
