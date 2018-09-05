#include "libFireBird.h"

inline dword FIS_fwApplTap_CallEventHandler(void)
{
  TRACEENTER;

  static dword          fwApplTap_CallEventHandler = 0;

  if(!fwApplTap_CallEventHandler)
    fwApplTap_CallEventHandler = TryResolve("_Z24ApplTap_CallEventHandlertjj");

  TRACEEXIT;
  return fwApplTap_CallEventHandler;
}
