#include "../libFireBird.h"

inline dword FIS_fwApplChannel_GetBer(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplChannel_GetBer");
  #endif

  static dword          _ApplChannel_GetBer = 0;

  if(!_ApplChannel_GetBer)
    _ApplChannel_GetBer = TryResolve("_Z18ApplChannel_GetBerhPh");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplChannel_GetBer;
}
