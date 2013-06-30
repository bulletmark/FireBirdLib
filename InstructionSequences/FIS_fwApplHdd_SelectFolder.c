#include "../libFireBird.h"

inline dword FIS_fwApplHdd_SelectFolder(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplHdd_SelectFolder");
  #endif

  static dword          _ApplHdd_SelectFolder = 0;

  if(!_ApplHdd_SelectFolder)
    _ApplHdd_SelectFolder = TryResolve("_Z20ApplHdd_SelectFolderPvPKc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplHdd_SelectFolder;
}
