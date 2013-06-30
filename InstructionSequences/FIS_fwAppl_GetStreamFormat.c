#include "../libFireBird.h"

inline dword FIS_fwAppl_GetStreamFormat(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_GetStreamFormat");
  #endif

  static dword          _Appl_GetStreamFormat = 0;

  if(!_Appl_GetStreamFormat)
    _Appl_GetStreamFormat = TryResolve("_Z20Appl_GetStreamFormath");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_GetStreamFormat;
}
