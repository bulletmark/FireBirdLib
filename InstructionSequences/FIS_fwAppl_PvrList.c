#include "../libFireBird.h"

inline dword FIS_fwAppl_PvrList(void)
{
  TRACEENTER();

  static dword          _Appl_PvrList = 0;

  if(!_Appl_PvrList)
    _Appl_PvrList = TryResolve("_Z12Appl_PvrListjj");

  TRACEEXIT();
  return _Appl_PvrList;
}
