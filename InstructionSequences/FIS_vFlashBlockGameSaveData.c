#include "../libFireBird.h"

inline dword FIS_vFlashBlockGameSaveData(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_gameSaveData");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

