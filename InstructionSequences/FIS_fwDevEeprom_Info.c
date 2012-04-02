#include "../libFireBird.h"

inline dword FIS_fwDevEeprom_Info(void)
{
  static dword          _DevEeprom_Info = 0;

  if (!_DevEeprom_Info)
    _DevEeprom_Info = TryResolve("DevEeprom_Info");

  return _DevEeprom_Info;
}
