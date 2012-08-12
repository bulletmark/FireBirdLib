#include "../libFireBird.h"

inline dword FIS_vFlashBlockFavoriteGroup(void)
{
  static dword          *vFlashFavGrp = 0;

  if(!vFlashFavGrp)
  {
    vFlashFavGrp = (dword*)TryResolve("_favGrp");
    if(!vFlashFavGrp) return 0;
  }

  return *vFlashFavGrp;
}
