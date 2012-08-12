#include "../libFireBird.h"

inline dword FIS_vFlashBlockDLNAData(void)
{
  static dword          *vFlashDlnaData = 0;

  if(!vFlashDlnaData)
  {
    vFlashDlnaData = (dword*)TryResolve("_dlnaData");
    if(!vFlashDlnaData) return 0;
  }

  return *vFlashDlnaData;
}
