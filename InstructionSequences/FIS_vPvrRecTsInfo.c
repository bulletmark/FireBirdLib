#include "../libFireBird.h"

inline dword FIS_vPvrRecTsInfo(void)
{
  TRACEENTER();

  static dword          vpvrRecTsInfo = 0;

  if(!vpvrRecTsInfo)
    vpvrRecTsInfo = TryResolve("_pvrRecTsInfo");

  TRACEEXIT();
  return vpvrRecTsInfo;
}
