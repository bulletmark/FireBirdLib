#include "../libFireBird.h"

inline dword FIS_fwAppl_StopTempRec(void)
{
  static dword          _Appl_StopTempRec = 0;

  if (!_Appl_StopTempRec)
    _Appl_StopTempRec = TryResolve("_Z16Appl_StopTempRecbb");

  return _Appl_StopTempRec;
}
