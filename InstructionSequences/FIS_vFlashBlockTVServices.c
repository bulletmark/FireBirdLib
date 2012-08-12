#include "../libFireBird.h"

inline dword FIS_vFlashBlockTVServices(void)
{
  static dword          *vFlashTVService = 0;

  if(!vFlashTVService)
  {
    vFlashTVService = (dword*)TryResolve("_tvSvc");
    if(!vFlashTVService) return 0;
  }

  return *vFlashTVService;
}
