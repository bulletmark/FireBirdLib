#include "../libFireBird.h"

inline dword FIS_vEEPROM(void)
{
  TRACEENTER();

  static dword         *_applEepromAddr;

  if(!_applEepromAddr)
    _applEepromAddr = (dword*)TryResolve("_applEepromAddr");

  TRACEEXIT();
  return (_applEepromAddr ? *_applEepromAddr : 0);
}
