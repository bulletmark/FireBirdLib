#include "../libFireBird.h"

inline dword FIS_fwAppl_InitTempRec(void)
{
  static dword          fwAppl_InitTempRec = 0;

  if (!fwAppl_InitTempRec)
    fwAppl_InitTempRec = TryResolve("_Z16Appl_InitTempRecv");

  return fwAppl_InitTempRec;
}
