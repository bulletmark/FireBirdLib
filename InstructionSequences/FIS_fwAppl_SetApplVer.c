#include "../libFireBird.h"

inline dword FIS_fwAppl_SetApplVer(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_SetApplVer");
  #endif

  static dword          fwAppl_SetApplVer = 0;

  if(!fwAppl_SetApplVer)
    fwAppl_SetApplVer = TryResolve("_Z15Appl_SetApplVerPc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwAppl_SetApplVer;
}
