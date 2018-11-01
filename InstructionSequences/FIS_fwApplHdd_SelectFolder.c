#include "libFireBird.h"

inline dword FIS_fwApplHdd_SelectFolder(void)
{
  TRACEENTER();

  static dword          _ApplHdd_SelectFolder = 0;

  if(!_ApplHdd_SelectFolder)
    _ApplHdd_SelectFolder = TryResolve("_Z20ApplHdd_SelectFolderPvPKc");

  TRACEEXIT();
  return _ApplHdd_SelectFolder;
}
