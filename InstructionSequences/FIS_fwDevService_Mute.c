#include "../libFireBird.h"

inline dword FIS_fwDevService_Mute(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwDevService_Mute");
  #endif

  static dword          _DevService_Mute = 0;

  if(!_DevService_Mute)
    _DevService_Mute = TryResolve("DevService_Mute");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _DevService_Mute;
}
