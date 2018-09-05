#include "libFireBird.h"

inline dword FIS_fwDevService_Mute(void)
{
  TRACEENTER;

  static dword          _DevService_Mute = 0;

  if(!_DevService_Mute)
    _DevService_Mute = TryResolve("DevService_Mute");

  TRACEEXIT;
  return _DevService_Mute;
}
