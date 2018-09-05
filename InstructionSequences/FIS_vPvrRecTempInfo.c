#include "libFireBird.h"

inline dword FIS_vPvrRecTempInfo(void)
{
  TRACEENTER;

  static dword          vpvrRecTempInfo = 0;

  if(!vpvrRecTempInfo)
    vpvrRecTempInfo = TryResolve("_pvrRecTempInfo");

  TRACEEXIT;
  return vpvrRecTempInfo;
}
