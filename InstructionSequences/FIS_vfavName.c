#include "../libFireBird.h"

inline dword FIS_vfavName(void)
{
  static dword          vfavName = 0;

  if (!vfavName)
    vfavName = TryResolve("_favName");

  return vfavName;
}
