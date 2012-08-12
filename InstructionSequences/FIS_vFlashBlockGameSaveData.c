#include "../libFireBird.h"

inline dword FIS_vFlashBlockGameSaveData(void)
{
  static dword          *vFlashGameSaveData = 0;

  if(!vFlashGameSaveData)
  {
    vFlashGameSaveData = (dword*)TryResolve("_gameSaveData");
    if(!vFlashGameSaveData) return 0;
  }

  return *vFlashGameSaveData;
}
