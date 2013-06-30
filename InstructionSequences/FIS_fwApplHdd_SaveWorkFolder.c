#include "../libFireBird.h"

inline dword FIS_fwApplHdd_SaveWorkFolder(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplHdd_SaveWorkFolder");
  #endif

  static dword          _ApplHdd_SaveWorkFolder = 0;

  if(!_ApplHdd_SaveWorkFolder)
    _ApplHdd_SaveWorkFolder = TryResolve("_Z22ApplHdd_SaveWorkFolderv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplHdd_SaveWorkFolder;
}
