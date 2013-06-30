#include "../libFireBird.h"

inline dword FIS_fwAppl_WriteFlash(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_WriteFlash");
  #endif

  static dword          _Appl_WriteFlash = 0;

  if(!_Appl_WriteFlash)
    _Appl_WriteFlash = TryResolve("_Z15Appl_WriteFlashb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_WriteFlash;
}
