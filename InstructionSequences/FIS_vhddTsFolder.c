#include "../libFireBird.h"

inline dword FIS_vHddTsFolder(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vHddTsFolder");
  #endif

  static dword          _hddTsFolder = 0;

  if(!_hddTsFolder)
    _hddTsFolder = TryResolve("_hddTsFolder");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _hddTsFolder;
}
