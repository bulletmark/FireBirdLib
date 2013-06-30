#include "../libFireBird.h"

inline dword FIS_fwPutDevEvt(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwPutDevEvt");
  #endif

  static dword          fwPutDevEvt = 0;

  if(!fwPutDevEvt)
    fwPutDevEvt = TryResolve("PutDevEvt");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwPutDevEvt;
}
