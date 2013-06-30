#include "../libFireBird.h"

inline dword FIS_fwApplTap_GetEmptyTask(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplTap_GetEmptyTask");
  #endif

  static dword          _ApplTap_GetEmptyTask = 0;

  if(!_ApplTap_GetEmptyTask)
    _ApplTap_GetEmptyTask = TryResolve("_Z20ApplTap_GetEmptyTaskv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplTap_GetEmptyTask;
}
