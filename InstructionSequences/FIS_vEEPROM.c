#include "../libFireBird.h"

inline dword FIS_vEEPROM(void)
{
  static dword         *_applEepromAddr;

  if(!_applEepromAddr)
    _applEepromAddr = (dword*)TryResolve("_applEepromAddr");

  return (_applEepromAddr ? *_applEepromAddr : 0);
}
