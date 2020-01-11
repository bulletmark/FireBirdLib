#include "libFireBird.h"

inline dword FIS_vgmt(void)
{
  TRACEENTER();

  static dword          vgmt = 0;

  if(!vgmt)
    vgmt = TryResolve("_gmt");

  TRACEEXIT();
  return vgmt;
}
