#include "../libFireBird.h"

inline dword FIS_fwAppl_PvrList_SetListType(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_PvrList_SetListType");
  #endif

  static dword          _Appl_PvrList_SetListType = 0;

  if(!_Appl_PvrList_SetListType)
    _Appl_PvrList_SetListType = TryResolve("_Z24Appl_PvrList_SetListTypei");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_PvrList_SetListType;
}
