#include "../libFireBird.h"

inline dword FIS_fwApplChannel_GetAgc(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplChannel_GetAgc");
  #endif

  static dword          _ApplChannel_GetAgc = 0;

  if(!_ApplChannel_GetAgc)
    _ApplChannel_GetAgc = TryResolve("_Z18ApplChannel_GetAgchPh");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplChannel_GetAgc;
}
