#include "../libFireBird.h"

inline dword FIS_vEEPROMPin(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vEEPROMPin");
  #endif

  static dword        vEEPROMPin = 0;

  if(!vEEPROMPin)
    vEEPROMPin = TryResolve("_parentalInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vEEPROMPin;
}
