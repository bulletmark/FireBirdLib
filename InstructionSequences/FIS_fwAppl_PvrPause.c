#include "libFireBird.h"

inline dword FIS_fwAppl_PvrPause(void)
{
  TRACEENTER;

  static dword          _Appl_PvrPause = 0;

  if(!_Appl_PvrPause)
    _Appl_PvrPause = TryResolve("_Z13Appl_PvrPauseb");

  TRACEEXIT;
  return _Appl_PvrPause;
}
