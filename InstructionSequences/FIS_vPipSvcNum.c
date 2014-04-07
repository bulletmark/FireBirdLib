#include "../libFireBird.h"

inline dword FIS_vPipSvcNum(void)
{
  TRACEENTER();

  static dword          _pipSvcNum = 0;

  if(!_pipSvcNum)
    _pipSvcNum = TryResolve("_pipSvcNum");

  TRACEEXIT();
  return _pipSvcNum;
}
