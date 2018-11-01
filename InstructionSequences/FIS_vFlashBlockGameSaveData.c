#include "libFireBird.h"

inline dword FIS_vFlashBlockGameSaveData(void)
{
  TRACEENTER();

  static dword          *vFlashGameSaveData = 0;

  if(!vFlashGameSaveData)
    vFlashGameSaveData = (dword*)TryResolve("_gameSaveData");

  TRACEEXIT();
  return (vFlashGameSaveData ? *vFlashGameSaveData : 0);
}
