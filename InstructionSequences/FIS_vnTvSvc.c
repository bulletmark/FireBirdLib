#include "libFireBird.h"

inline dword FIS_vnTvSvc(void)
{
  TRACEENTER();

  static dword          vnTvSvc = 0;

  if(!vnTvSvc)
    vnTvSvc = TryResolve("_nTvSvc");

  TRACEEXIT();
  return vnTvSvc;
}
