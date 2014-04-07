#include "../libFireBird.h"

inline dword FIS_vfrontfd(void)
{
  TRACEENTER();

  static dword          vfrontfd = 0;

  if(!vfrontfd)
    vfrontfd = TryResolve("_frontfd");

  TRACEEXIT();
  return vfrontfd;
}
