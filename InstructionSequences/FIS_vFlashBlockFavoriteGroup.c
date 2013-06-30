#include "../libFireBird.h"

inline dword FIS_vFlashBlockFavoriteGroup(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockFavoriteGroup");
  #endif

  static dword          *vFlashFavGrp = 0;

  if(!vFlashFavGrp)
    vFlashFavGrp = (dword*)TryResolve("_favGrp");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashFavGrp ? *vFlashFavGrp : 0);
}
