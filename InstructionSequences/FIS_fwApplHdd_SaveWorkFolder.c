#include "../libFireBird.h"

inline dword FIS_fwApplHdd_SaveWorkFolder(void)
{
  static dword          _ApplHdd_SaveWorkFolder = 0;

  if (!_ApplHdd_SaveWorkFolder)
    _ApplHdd_SaveWorkFolder = TryResolve("_Z22ApplHdd_SaveWorkFolderv");

  return _ApplHdd_SaveWorkFolder;
}
