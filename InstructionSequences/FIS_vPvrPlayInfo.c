#include "libFireBird.h"

inline dword FIS_vPvrPlayInfo(void)
{
  TRACEENTER();

  static dword          vPvrPlayInfo = 0;

  if(!vPvrPlayInfo)
    vPvrPlayInfo = TryResolve("_pvrPlayInfo");

  TRACEEXIT();
  return vPvrPlayInfo;
}
