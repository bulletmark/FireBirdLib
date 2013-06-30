#include "../libFireBird.h"

inline dword FIS_fwApplHdd_SetWorkFolder(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplHdd_SetWorkFolder");
  #endif

  static dword          _ApplHdd_SetWorkFolder = 0;

  if(!_ApplHdd_SetWorkFolder)
    _ApplHdd_SetWorkFolder = TryResolve("_Z21ApplHdd_SetWorkFolderPv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplHdd_SetWorkFolder;
}
