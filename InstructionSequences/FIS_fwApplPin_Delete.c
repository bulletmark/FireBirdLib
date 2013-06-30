#include "../libFireBird.h"

inline dword FIS_fwApplPin_Delete(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplPin_Delete");
  #endif

  static dword          _ApplPin_Delete = 0;

  if(!_ApplPin_Delete)
    _ApplPin_Delete = TryResolve("_Z14ApplPin_Deletev");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplPin_Delete;
}
