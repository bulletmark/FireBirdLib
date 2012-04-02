#include "../libFireBird.h"

inline dword FIS_fwAppl_WriteRecInfo(void)
{
  static dword          fwAppl_WriteRecInfo = 0;

  if (!fwAppl_WriteRecInfo)
    fwAppl_WriteRecInfo = TryResolve("_Z17Appl_WriteRecInfoj");

  return fwAppl_WriteRecInfo;
}
