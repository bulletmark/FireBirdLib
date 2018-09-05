#include "libFireBird.h"

inline dword FIS_fwAppl_ImportChData(void)
{
  TRACEENTER;

  static dword          _Appl_ImportChData = 0;

  if(!_Appl_ImportChData)
    _Appl_ImportChData = TryResolve("_Z17Appl_ImportChDataPKc");

  TRACEEXIT;
  return _Appl_ImportChData;
}
