#include "../libFireBird.h"

inline dword FIS_fwDevService_Mute(void)
{
  static dword          _DevService_Mute = 0;

  if (!_DevService_Mute)
    _DevService_Mute = TryResolve("DevService_Mute");

  return _DevService_Mute;
}
