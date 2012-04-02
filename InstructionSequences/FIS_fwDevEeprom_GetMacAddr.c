#include "../libFireBird.h"

inline dword FIS_fwDevEeprom_GetMacAddr(void)
{
  static dword          fwDevEeprom_GetMacAddr = 0;

  if (!fwDevEeprom_GetMacAddr)
    fwDevEeprom_GetMacAddr = TryResolve("DevEeprom_GetMacAddr");

  return fwDevEeprom_GetMacAddr;
}
