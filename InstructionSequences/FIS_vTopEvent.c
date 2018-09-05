#include "libFireBird.h"

inline dword FIS_vTopEvent(void)
{
  TRACEENTER;

  static dword          vtopEvent = 0;

  if(!vtopEvent)
    vtopEvent = TryResolve("_topEvent");

  TRACEEXIT;
  return vtopEvent;
}
