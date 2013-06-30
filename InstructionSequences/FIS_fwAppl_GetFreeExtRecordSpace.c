#include "../libFireBird.h"

inline dword FIS_fwAppl_GetFreeExtRecordSpace(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_GetFreeExtRecordSpace");
  #endif

  static dword          _Appl_GetFreeExtRecordSpace = 0;

  if(!_Appl_GetFreeExtRecordSpace)
    _Appl_GetFreeExtRecordSpace = TryResolve("_Z26Appl_GetFreeExtRecordSpacePc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_GetFreeExtRecordSpace;
}
