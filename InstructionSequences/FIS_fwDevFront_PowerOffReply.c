#include "../libFireBird.h"

inline dword FIS_fwDevFront_PowerOffReply(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwDevFront_PowerOffReply");
  #endif

  static dword          fwDevFront_PowerOffReply = 0;

  if(!fwDevFront_PowerOffReply)
    fwDevFront_PowerOffReply = TryResolve("DevFront_PowerOffReply");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwDevFront_PowerOffReply;
}
