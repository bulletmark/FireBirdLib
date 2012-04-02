#include "../libFireBird.h"

inline dword FIS_fwAppl_PvrList(void)
{
  static dword          _Appl_PvrList = 0;

  if(!_Appl_PvrList) _Appl_PvrList = TryResolve("_Z12Appl_PvrListjj");

  return _Appl_PvrList;
}
