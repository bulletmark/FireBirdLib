#include "../libFireBird.h"

inline dword FIS_vFlashBlockRadioServices(void)
{
  static dword          *vFlashRadioSvc = 0;

  if(!vFlashRadioSvc)
  {
    vFlashRadioSvc = (dword*)TryResolve("_radioSvc");
    if(!vFlashRadioSvc) return 0;
  }

  return *vFlashRadioSvc;
}
