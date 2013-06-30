#include "../libFireBird.h"

inline dword FIS_fwAppl_InitTempRec(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_InitTempRec");
  #endif

  static dword          fwAppl_InitTempRec = 0;

  if(!fwAppl_InitTempRec)
    fwAppl_InitTempRec = TryResolve("_Z16Appl_InitTempRecv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwAppl_InitTempRec;
}
