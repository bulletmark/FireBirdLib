#include "../libFireBird.h"

inline dword FIS_fwAppl_WaitEvt(void)
{
  TRACEENTER();

  static dword          _Appl_WaitEvt = 0;

  if(!_Appl_WaitEvt)
    _Appl_WaitEvt = TryResolve("_Z12Appl_WaitEvtjPjjjj");

  TRACEEXIT();
  return _Appl_WaitEvt;
}
