#include                "libFireBird.h"

bool ApplPin_IsLockPopup(void)
{
  TRACEENTER();

  dword (*__ApplPin_IsLockPopup)(void);
  bool ret = FALSE;

  __ApplPin_IsLockPopup = (void*)FIS_fwApplPin_IsLockPopup();
  if(__ApplPin_IsLockPopup) ret = __ApplPin_IsLockPopup();

  TRACEEXIT();
  return ret;
}
