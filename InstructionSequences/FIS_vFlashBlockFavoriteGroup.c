#include "libFireBird.h"

inline dword FIS_vFlashBlockFavoriteGroup(void)
{
  TRACEENTER();

  static dword          *vFlashFavGrp = 0;

  if(!vFlashFavGrp)
    vFlashFavGrp = (dword*)TryResolve("_favGrp");

  TRACEEXIT();
  return (vFlashFavGrp ? *vFlashFavGrp : 0);
}
