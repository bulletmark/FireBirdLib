#include "../libFireBird.h"

inline dword FIS_fwApplHdd_RestoreWorkFolder(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplHdd_RestoreWorkFolder");
  #endif

  static dword          _ApplHdd_RestoreWorkFolder = 0;

  if(!_ApplHdd_RestoreWorkFolder)
    _ApplHdd_RestoreWorkFolder = TryResolve("_Z25ApplHdd_RestoreWorkFolderv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplHdd_RestoreWorkFolder;
}
