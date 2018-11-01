#include "libFireBird.h"

inline dword FIS_vfavName(void)
{
  TRACEENTER();

  static dword          vfavName = 0;

  if(!vfavName)
    vfavName = TryResolve("_favName");

  TRACEEXIT();
  return vfavName;
}
