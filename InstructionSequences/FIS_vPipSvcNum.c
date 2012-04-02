#include "../libFireBird.h"

inline dword FIS_vPipSvcNum(void)
{
  static dword          _pipSvcNum = 0;

  if (!_pipSvcNum)
    _pipSvcNum = TryResolve("_pipSvcNum");

  return _pipSvcNum;
}
