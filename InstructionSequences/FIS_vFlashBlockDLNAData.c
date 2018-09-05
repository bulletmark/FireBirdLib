#include "libFireBird.h"

inline dword FIS_vFlashBlockDLNAData(void)
{
  TRACEENTER;

  static dword          *vFlashDlnaData = 0;

  if(!vFlashDlnaData)
    vFlashDlnaData = (dword*)TryResolve("_dlnaData");

  TRACEEXIT;
  return (vFlashDlnaData ? *vFlashDlnaData : 0);
}
