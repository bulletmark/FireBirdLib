#include "libFireBird.h"

inline dword FIS_fwEeprom_DirectWrite(void)
{
  TRACEENTER;

  static dword          _Eeprom_DirectWrite = 0;

  if(!_Eeprom_DirectWrite)
    _Eeprom_DirectWrite = TryResolve("Eeprom_DirectWrite");

  TRACEEXIT;
  return _Eeprom_DirectWrite;
}
