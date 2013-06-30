#include "../libFireBird.h"

inline dword FIS_vFlashBlockTVServices(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockTVServices");
  #endif

  static dword          *vFlashTVService = 0;

  if(!vFlashTVService)
    vFlashTVService = (dword*)TryResolve("_tvSvc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashTVService ? *vFlashTVService : 0);
}
