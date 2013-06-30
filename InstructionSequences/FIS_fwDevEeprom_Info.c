#include "../libFireBird.h"

inline dword FIS_fwDevEeprom_Info(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwDevEeprom_Info");
  #endif

  static dword          _DevEeprom_Info = 0;

  if(!_DevEeprom_Info)
    _DevEeprom_Info = TryResolve("DevEeprom_Info");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _DevEeprom_Info;
}
