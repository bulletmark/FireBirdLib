#include "../libFireBird.h"

inline dword FIS_vnPipSvcNum(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vnPipSvcNum");
  #endif

  static dword          _nPipSvcNum = 0;

  if(!_nPipSvcNum)
    _nPipSvcNum = TryResolve("_nPipSvcNum");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _nPipSvcNum;
}
