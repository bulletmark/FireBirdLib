#include "libFireBird.h"

inline dword FIS_fwApplPin_IsLockPopup(void)
{
  TRACEENTER();

  static dword          _ApplPin_IsLockPopup = 0;

  if(!_ApplPin_IsLockPopup)
    _ApplPin_IsLockPopup = TryResolve("_Z19ApplPin_IsLockPopupv");

  TRACEEXIT();
  return _ApplPin_IsLockPopup;
}
