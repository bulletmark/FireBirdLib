#include "../libFireBird.h"

inline dword FIS_fwApplHdd_SetWorkFolder(void)
{
  static dword          _ApplHdd_SetWorkFolder = 0;

  if (!_ApplHdd_SetWorkFolder)
    _ApplHdd_SetWorkFolder = TryResolve("_Z21ApplHdd_SetWorkFolderPv");

  return _ApplHdd_SetWorkFolder;
}
