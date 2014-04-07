#include "../libFireBird.h"

inline dword FIS_vnPipSvcNum(void)
{
  TRACEENTER();

  static dword          _nPipSvcNum = 0;

  if(!_nPipSvcNum)
    _nPipSvcNum = TryResolve("_nPipSvcNum");

  TRACEEXIT();
  return _nPipSvcNum;
}
