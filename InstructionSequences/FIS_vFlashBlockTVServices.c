#include "libFireBird.h"

inline dword FIS_vFlashBlockTVServices(void)
{
  TRACEENTER;

  static dword          *vFlashTVService = 0;

  if(!vFlashTVService)
    vFlashTVService = (dword*)TryResolve("_tvSvc");

  TRACEEXIT;
  return (vFlashTVService ? *vFlashTVService : 0);
}
