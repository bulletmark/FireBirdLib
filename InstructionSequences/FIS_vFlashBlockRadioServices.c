#include "../libFireBird.h"

inline dword FIS_vFlashBlockRadioServices(void)
{
  TRACEENTER();

  static dword          *vFlashRadioSvc = 0;

  TRACEEXIT();
  if(!vFlashRadioSvc)
    vFlashRadioSvc = (dword*)TryResolve("_radioSvc");

  return (vFlashRadioSvc ? *vFlashRadioSvc : 0);
}
