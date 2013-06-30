#include "../libFireBird.h"

inline dword FIS_fwApplIcelink_EitFromHdd(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplIcelink_EitFromHdd");
  #endif

  static dword          _ApplIcelink_EitFromHdd = 0;
  static bool           FirstCall = TRUE;

  if(FirstCall)
  {
    _ApplIcelink_EitFromHdd = TryResolve("_Z22ApplIcelink_EitFromHddv");
    FirstCall = FALSE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplIcelink_EitFromHdd;
}
