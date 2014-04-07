#include "../libFireBird.h"

inline dword FIS_fwAppl_PvrList_SetListType(void)
{
  TRACEENTER();

  static dword          _Appl_PvrList_SetListType = 0;

  if(!_Appl_PvrList_SetListType)
    _Appl_PvrList_SetListType = TryResolve("_Z24Appl_PvrList_SetListTypei");

  TRACEEXIT();
  return _Appl_PvrList_SetListType;
}
