#include "../libFireBird.h"

inline dword FIS_vOsdOutBuf(void)
{
  TRACEENTER();

  static dword          vosdOutBuf = 0;

  if(!vosdOutBuf)
    vosdOutBuf = TryResolve("_osdOutBuf");

  TRACEEXIT();
  return vosdOutBuf;
}
