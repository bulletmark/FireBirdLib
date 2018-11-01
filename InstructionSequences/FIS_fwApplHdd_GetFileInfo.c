#include "libFireBird.h"

inline dword FIS_fwApplHdd_GetFileInfo(void)
{
  TRACEENTER();

  static dword          _ApplHdd_GetFileInfo = 0;

  if(!_ApplHdd_GetFileInfo)
    _ApplHdd_GetFileInfo = TryResolve("_Z19ApplHdd_GetFileInfotPjS_hh");

  TRACEEXIT();
  return _ApplHdd_GetFileInfo;
}
