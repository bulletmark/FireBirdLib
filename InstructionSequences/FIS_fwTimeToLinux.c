#include "../libFireBird.h"

inline dword FIS_fwTimeToLinux(void)
{
  TRACEENTER();

  static dword          _TimeToLinux = 0;

  if(!_TimeToLinux)
    _TimeToLinux = TryResolve("PvrTimeToLinux");

  TRACEEXIT();
  return _TimeToLinux;
}
