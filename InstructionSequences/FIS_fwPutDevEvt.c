#include "../libFireBird.h"

inline dword FIS_fwPutDevEvt(void)
{
  static dword          fwPutDevEvt = 0;

  if (!fwPutDevEvt)
    fwPutDevEvt = TryResolve("PutDevEvt");

  return fwPutDevEvt;
}
