#include "../libFireBird.h"

inline dword FIS_fwApplHdd_FileCutPaste(void)
{
  static dword          _ApplHdd_FileCutPaste = 0;

  if (!_ApplHdd_FileCutPaste)
    _ApplHdd_FileCutPaste = TryResolve("_Z20ApplHdd_FileCutPastePKcjjS0_");

  return _ApplHdd_FileCutPaste;
}
