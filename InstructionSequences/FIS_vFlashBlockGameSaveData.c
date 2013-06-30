#include "../libFireBird.h"

inline dword FIS_vFlashBlockGameSaveData(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockGameSaveData");
  #endif

  static dword          *vFlashGameSaveData = 0;

  if(!vFlashGameSaveData)
    vFlashGameSaveData = (dword*)TryResolve("_gameSaveData");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashGameSaveData ? *vFlashGameSaveData : 0);
}
