#include "../libFireBird.h"

inline dword FIS_fwApplHdd_FreeSize(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplHdd_FreeSize");
  #endif

  static dword          _ApplHdd_FreeSize = 0;

  if(!_ApplHdd_FreeSize)
    _ApplHdd_FreeSize = TryResolve("_Z16ApplHdd_FreeSizePKcb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplHdd_FreeSize;
}
