#include "libFireBird.h"

inline dword FIS_vbookmarkTime(void)
{
  TRACEENTER();

  static dword          vbookmarkTime = 0;

  if(!vbookmarkTime)
    vbookmarkTime = TryResolve("_bookmarkTime");

  TRACEEXIT();
  return vbookmarkTime;
}
