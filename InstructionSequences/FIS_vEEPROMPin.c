#include "libFireBird.h"

inline dword FIS_vEEPROMPin(void)
{
  TRACEENTER();

  static dword        vEEPROMPin = 0;

  if(!vEEPROMPin)
    vEEPROMPin = TryResolve("_parentalInfo");

  TRACEEXIT();
  return vEEPROMPin;
}
