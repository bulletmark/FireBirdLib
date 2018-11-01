#include "libFireBird.h"

inline dword FIS_fwAppl_WriteRecInfo(void)
{
  TRACEENTER();

  static dword          fwAppl_WriteRecInfo = 0;

  if(!fwAppl_WriteRecInfo)
    fwAppl_WriteRecInfo = TryResolve("_Z17Appl_WriteRecInfoj");

  TRACEEXIT();
  return fwAppl_WriteRecInfo;
}
