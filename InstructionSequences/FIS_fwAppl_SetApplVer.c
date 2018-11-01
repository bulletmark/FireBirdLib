#include "libFireBird.h"

inline dword FIS_fwAppl_SetApplVer(void)
{
  TRACEENTER();

  static dword          fwAppl_SetApplVer = 0;

  if(!fwAppl_SetApplVer)
    fwAppl_SetApplVer = TryResolve("_Z15Appl_SetApplVerPc");

  TRACEEXIT();
  return fwAppl_SetApplVer;
}
