#include "../libFireBird.h"

inline dword FIS_fwAppl_ImportChData(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_ImportChData");
  #endif

  static dword          _Appl_ImportChData = 0;

  if(!_Appl_ImportChData)
    _Appl_ImportChData = TryResolve("_Z17Appl_ImportChDataPKc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_ImportChData;
}
