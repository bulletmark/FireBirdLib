#include "../libFireBird.h"

inline dword FIS_vOsdMap (void)
{
  static dword          vOSDMap = 0;

  if (!vOSDMap)
    vOSDMap = TryResolve("_osdInfo");

  return vOSDMap;
}
