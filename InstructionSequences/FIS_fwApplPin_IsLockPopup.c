#include "../libFireBird.h"

inline dword FIS_fwApplPin_IsLockPopup(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplPin_IsLockPopup");
  #endif

  static dword          _ApplPin_IsLockPopup = 0;

  if(!_ApplPin_IsLockPopup)
    _ApplPin_IsLockPopup = TryResolve("_Z19ApplPin_IsLockPopupv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplPin_IsLockPopup;
}
