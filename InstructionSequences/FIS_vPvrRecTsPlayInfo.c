#include "../libFireBird.h"

inline dword FIS_vPvrRecTsPlayInfo(void)
{
  static dword          vpvrRecTsPlayInfo = 0;

  if (!vpvrRecTsPlayInfo)
    vpvrRecTsPlayInfo = TryResolve("_pvrRecTsPlayInfo");

  return vpvrRecTsPlayInfo;
}
