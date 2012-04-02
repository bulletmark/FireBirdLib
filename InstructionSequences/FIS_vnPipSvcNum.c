#include "../libFireBird.h"

inline dword FIS_vnPipSvcNum(void)
{
  static dword          _nPipSvcNum = 0;

  if (!_nPipSvcNum)
    _nPipSvcNum = TryResolve("_nPipSvcNum");

  return _nPipSvcNum;
}
