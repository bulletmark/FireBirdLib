#include                "../libFireBird.h"

bool ApplPin_IsLockPopup(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ApplPin_IsLockPopup");
  #endif

  dword (*__ApplPin_IsLockPopup)(void);
  bool ret = FALSE;

  __ApplPin_IsLockPopup = (void*)FIS_fwApplPin_IsLockPopup();
  if(__ApplPin_IsLockPopup) ret = __ApplPin_IsLockPopup();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
