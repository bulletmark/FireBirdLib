#include "libFireBird.h"

inline dword FIS_fwApplIcelink_EitFromHdd(void)
{
  TRACEENTER();

  static dword          _ApplIcelink_EitFromHdd = 0;
  static bool           FirstCall = TRUE;

  if(FirstCall)
  {
    _ApplIcelink_EitFromHdd = TryResolve("_Z22ApplIcelink_EitFromHddv");
    FirstCall = FALSE;
  }

  TRACEEXIT();
  return _ApplIcelink_EitFromHdd;
}
