#include "../libFireBird.h"

inline dword FIS_fwAppl_TimeToLocal(void)
{
  static dword          fwAppl_TimeToLocal = 0;

  if (!fwAppl_TimeToLocal)
    fwAppl_TimeToLocal = TryResolve("_Z16Appl_TimeToLocalj");

  return fwAppl_TimeToLocal;
}
