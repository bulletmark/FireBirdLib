#include "../libFireBird.h"

inline dword FIS_vEEPROM(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vEEPROM");
  #endif

  static dword         *_applEepromAddr;

  if(!_applEepromAddr)
    _applEepromAddr = (dword*)TryResolve("_applEepromAddr");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (_applEepromAddr ? *_applEepromAddr : 0);
}
