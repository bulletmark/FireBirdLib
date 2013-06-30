#include "../libFireBird.h"

inline dword FIS_vnTvSvc(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vnTvSvc");
  #endif

  static dword          vnTvSvc = 0;

  if(!vnTvSvc)
    vnTvSvc = TryResolve("_nTvSvc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vnTvSvc;
}
