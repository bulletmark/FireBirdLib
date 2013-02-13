#include "../libFireBird.h"

inline dword FIS_vbookmarkTime(void)
{
  static dword          vbookmarkTime = 0;

  if(!vbookmarkTime)
    vbookmarkTime = TryResolve("_bookmarkTime");

  return vbookmarkTime;
}
