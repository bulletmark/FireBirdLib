#include "../libFireBird.h"

inline dword FIS_vnRadioSvc(void)
{
  static dword          vnRadioSvc = 0;

  if (!vnRadioSvc)
    vnRadioSvc = TryResolve("_nRadioSvc");

  return vnRadioSvc;
}
