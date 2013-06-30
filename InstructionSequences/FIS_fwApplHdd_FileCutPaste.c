#include "../libFireBird.h"

inline dword FIS_fwApplHdd_FileCutPaste(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplHdd_FileCutPaste");
  #endif

  static dword          _ApplHdd_FileCutPaste = 0;

  if(!_ApplHdd_FileCutPaste)
    _ApplHdd_FileCutPaste = TryResolve("_Z20ApplHdd_FileCutPastePKcjjS0_");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplHdd_FileCutPaste;
}
