#include "../libFireBird.h"

inline dword FIS_vFlashBlockRadioServices(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_radioSvc");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

