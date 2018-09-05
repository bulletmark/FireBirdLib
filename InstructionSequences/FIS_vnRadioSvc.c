#include "libFireBird.h"

inline dword FIS_vnRadioSvc(void)
{
  TRACEENTER;

  static dword          vnRadioSvc = 0;

  if(!vnRadioSvc)
    vnRadioSvc = TryResolve("_nRadioSvc");

  TRACEEXIT;
  return vnRadioSvc;
}
