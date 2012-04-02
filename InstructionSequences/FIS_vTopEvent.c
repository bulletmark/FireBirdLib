#include "../libFireBird.h"

inline dword FIS_vTopEvent(void)
{
  static dword          vtopEvent = 0;

  if (!vtopEvent)
    vtopEvent = TryResolve("_topEvent");

  return vtopEvent;
}
