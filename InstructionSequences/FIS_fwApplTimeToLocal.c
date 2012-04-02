#include                "../libFireBird.h"

inline dword FIS_fwApplTimeToLocal(void)
{
  static dword          Appl_TimeToLocal = 0;

  if(!Appl_TimeToLocal)
    Appl_TimeToLocal = TryResolve("_Z16Appl_TimeToLocalj");

  return Appl_TimeToLocal;
}
