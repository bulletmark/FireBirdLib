#include "../libFireBird.h"

inline dword FIS_fwApplHdd_GetFileInfo(void)
{
  static dword          _ApplHdd_GetFileInfo = 0;

  if (!_ApplHdd_GetFileInfo)
    _ApplHdd_GetFileInfo = TryResolve("_Z19ApplHdd_GetFileInfotPjS_hh");

  return _ApplHdd_GetFileInfo;
}
