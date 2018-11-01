#include "libFireBird.h"

inline dword FIS_fwApplHdd_FreeSize(void)
{
  TRACEENTER();

  static dword          _ApplHdd_FreeSize = 0;

  if(!_ApplHdd_FreeSize)
    _ApplHdd_FreeSize = TryResolve("_Z16ApplHdd_FreeSizePKcb");

  TRACEEXIT();
  return _ApplHdd_FreeSize;
}
