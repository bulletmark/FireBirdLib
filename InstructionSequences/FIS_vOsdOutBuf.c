#include "../libFireBird.h"

inline dword FIS_vOsdOutBuf(void)
{
  static dword          vosdOutBuf = 0;

  if (!vosdOutBuf)
    vosdOutBuf = TryResolve("_osdOutBuf");

  return vosdOutBuf;
}
