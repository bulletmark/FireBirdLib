#include "../libFireBird.h"

inline dword FIS_vHddTapFolder(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vHddTapFolder");
  #endif

  static dword          _hddTapFolder = 0;

  if(!_hddTapFolder)
    _hddTapFolder = TryResolve("_hddTapFolder");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _hddTapFolder;
}
