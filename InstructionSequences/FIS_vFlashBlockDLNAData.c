#include "../libFireBird.h"

inline dword FIS_vFlashBlockDLNAData(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockDLNAData");
  #endif

  static dword          *vFlashDlnaData = 0;

  if(!vFlashDlnaData)
    vFlashDlnaData = (dword*)TryResolve("_dlnaData");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashDlnaData ? *vFlashDlnaData : 0);
}
