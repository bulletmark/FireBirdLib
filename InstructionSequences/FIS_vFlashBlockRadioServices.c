#include "../libFireBird.h"

inline dword FIS_vFlashBlockRadioServices(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockRadioServices");
  #endif

  static dword          *vFlashRadioSvc = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  if(!vFlashRadioSvc)
    vFlashRadioSvc = (dword*)TryResolve("_radioSvc");

  return (vFlashRadioSvc ? *vFlashRadioSvc : 0);
}
