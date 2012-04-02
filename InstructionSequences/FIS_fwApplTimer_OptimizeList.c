#include "../libFireBird.h"

inline dword FIS_fwApplTimer_OptimizeList(void)
{
  static dword          _ApplTimer_OptimizeList = 0;

  if (!_ApplTimer_OptimizeList)
    _ApplTimer_OptimizeList = TryResolve("_Z22ApplTimer_OptimizeListv");

  return _ApplTimer_OptimizeList;
}
