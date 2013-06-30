#include "../libFireBird.h"

inline dword FIS_fwEeprom_DirectWrite(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwEeprom_DirectWrite");
  #endif

  static dword          _Eeprom_DirectWrite = 0;

  if(!_Eeprom_DirectWrite)
    _Eeprom_DirectWrite = TryResolve("Eeprom_DirectWrite");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Eeprom_DirectWrite;
}
