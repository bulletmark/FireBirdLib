#include "../libFireBird.h"

inline dword FIS_fwAppl_TimeToLocal(void)
{
  TRACEENTER();

  static dword          fwAppl_TimeToLocal = 0;

  if(!fwAppl_TimeToLocal)
    fwAppl_TimeToLocal = TryResolve("_Z16Appl_TimeToLocalj");

  TRACEEXIT();
  return fwAppl_TimeToLocal;
}
