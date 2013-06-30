#include "../libFireBird.h"

inline dword FIS_vPipSvcNum(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vPipSvcNum");
  #endif

  static dword          _pipSvcNum = 0;

  if(!_pipSvcNum)
    _pipSvcNum = TryResolve("_pipSvcNum");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _pipSvcNum;
}
