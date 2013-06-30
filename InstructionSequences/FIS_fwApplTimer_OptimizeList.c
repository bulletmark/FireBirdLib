#include "../libFireBird.h"

inline dword FIS_fwApplTimer_OptimizeList(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplTimer_OptimizeList");
  #endif

  static dword          _ApplTimer_OptimizeList = 0;

  if(!_ApplTimer_OptimizeList)
    _ApplTimer_OptimizeList = TryResolve("_Z22ApplTimer_OptimizeListv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplTimer_OptimizeList;
}
