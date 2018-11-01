#include "libFireBird.h"

inline dword FIS_vPvrRecTsPlayInfo(void)
{
  TRACEENTER();

  static dword          vpvrRecTsPlayInfo = 0;

  if(!vpvrRecTsPlayInfo)
    vpvrRecTsPlayInfo = TryResolve("_pvrRecTsPlayInfo");

  TRACEEXIT();
  return vpvrRecTsPlayInfo;
}
