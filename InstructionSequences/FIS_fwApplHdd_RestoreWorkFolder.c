#include "../libFireBird.h"

inline dword FIS_fwApplHdd_RestoreWorkFolder(void)
{
  static dword          _ApplHdd_RestoreWorkFolder = 0;

  if (!_ApplHdd_RestoreWorkFolder)
    _ApplHdd_RestoreWorkFolder = TryResolve("_Z25ApplHdd_RestoreWorkFolderv");

  return _ApplHdd_RestoreWorkFolder;
}
