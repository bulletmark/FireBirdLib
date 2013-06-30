#include "../libFireBird.h"

inline dword FIS_fwDevFront_PowerOffCancel(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwDevFront_PowerOffCancel");
  #endif

  static dword          fwDevFront_PowerOffCancel = 0;

  if(!fwDevFront_PowerOffCancel)
    fwDevFront_PowerOffCancel = TryResolve("DevFront_PowerOffCancel");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwDevFront_PowerOffCancel;
}
