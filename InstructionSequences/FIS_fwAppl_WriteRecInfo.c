#include "../libFireBird.h"

inline dword FIS_fwAppl_WriteRecInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_WriteRecInfo");
  #endif

  static dword          fwAppl_WriteRecInfo = 0;

  if(!fwAppl_WriteRecInfo)
    fwAppl_WriteRecInfo = TryResolve("_Z17Appl_WriteRecInfoj");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwAppl_WriteRecInfo;
}
