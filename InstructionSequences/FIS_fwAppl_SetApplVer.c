#include "../libFireBird.h"

inline dword FIS_fwAppl_SetApplVer(void)
{
  static dword          fwAppl_SetApplVer = 0;

  if (!fwAppl_SetApplVer)
    fwAppl_SetApplVer = TryResolve("_Z15Appl_SetApplVerPc");

  return fwAppl_SetApplVer;
}
