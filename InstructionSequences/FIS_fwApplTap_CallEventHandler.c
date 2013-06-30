#include "../libFireBird.h"

inline dword FIS_fwApplTap_CallEventHandler(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplTap_CallEventHandler");
  #endif

  static dword          fwApplTap_CallEventHandler = 0;

  if(!fwApplTap_CallEventHandler)
    fwApplTap_CallEventHandler = TryResolve("_Z24ApplTap_CallEventHandlertjj");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwApplTap_CallEventHandler;
}
