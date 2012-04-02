#include "../libFireBird.h"

inline dword FIS_vEEPROMPin (void)
{
    static dword        vEEPROMPin = 0;

  if (!vEEPROMPin)
    vEEPROMPin = TryResolve("_parentalInfo");

  return vEEPROMPin;
}
