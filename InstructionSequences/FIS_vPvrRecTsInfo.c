#include "../libFireBird.h"

inline dword FIS_vPvrRecTsInfo(void)
{
  static dword          vpvrRecTsInfo = 0;

  if (!vpvrRecTsInfo)
    vpvrRecTsInfo = TryResolve("_pvrRecTsInfo");

  return vpvrRecTsInfo;
}
