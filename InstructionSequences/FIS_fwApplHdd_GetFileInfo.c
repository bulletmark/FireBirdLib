#include "../libFireBird.h"

inline dword FIS_fwApplHdd_GetFileInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplHdd_GetFileInfo");
  #endif

  static dword          _ApplHdd_GetFileInfo = 0;

  if(!_ApplHdd_GetFileInfo)
    _ApplHdd_GetFileInfo = TryResolve("_Z19ApplHdd_GetFileInfotPjS_hh");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplHdd_GetFileInfo;
}
