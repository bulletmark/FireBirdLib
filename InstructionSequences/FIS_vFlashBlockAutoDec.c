#include "libFireBird.h"

inline dword FIS_vFlashBlockAutoDec(void)
{
  TRACEENTER();

  static dword          *vFlashAutoDec = 0;

  if(!vFlashAutoDec)
    vFlashAutoDec = (dword*)TryResolve("_autoDec");

  TRACEEXIT();
  return (vFlashAutoDec ? *vFlashAutoDec : 0);
}
