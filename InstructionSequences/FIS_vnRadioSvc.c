#include "../libFireBird.h"

inline dword FIS_vnRadioSvc(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vnRadioSvc");
  #endif

  static dword          vnRadioSvc = 0;

  if(!vnRadioSvc)
    vnRadioSvc = TryResolve("_nRadioSvc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vnRadioSvc;
}
