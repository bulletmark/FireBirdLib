#include "../libFireBird.h"

inline dword FIS_vFlashBlockAutoDec(void)
{
  static dword          *vFlashAutoDec = 0;

  if(!vFlashAutoDec)
  {
    vFlashAutoDec = (dword*)TryResolve("_autoDec");
    if(!vFlashAutoDec) return 0;
  }

  return *vFlashAutoDec;
}
