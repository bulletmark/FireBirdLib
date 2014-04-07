#include "../libFireBird.h"

inline dword FIS_fwApplHdd_FileCutPaste(void)
{
  TRACEENTER();

  static dword          _ApplHdd_FileCutPaste = 0;

  if(!_ApplHdd_FileCutPaste)
    _ApplHdd_FileCutPaste = TryResolve("_Z20ApplHdd_FileCutPastePKcjjS0_");

  TRACEEXIT();
  return _ApplHdd_FileCutPaste;
}
