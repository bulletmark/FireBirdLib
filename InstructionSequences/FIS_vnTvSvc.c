#include "../libFireBird.h"

inline dword FIS_vnTvSvc(void)
{
  static dword          vnTvSvc = 0;

  if (!vnTvSvc)
    vnTvSvc = TryResolve("_nTvSvc");

  return vnTvSvc;
}
