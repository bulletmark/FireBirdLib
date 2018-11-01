#include "libFireBird.h"

inline dword FIS_fwApplHdd_SetWorkFolder(void)
{
  TRACEENTER();

  static dword          _ApplHdd_SetWorkFolder = 0;

  if(!_ApplHdd_SetWorkFolder)
    _ApplHdd_SetWorkFolder = TryResolve("_Z21ApplHdd_SetWorkFolderPv");

  TRACEEXIT();
  return _ApplHdd_SetWorkFolder;
}
