#include "../libFireBird.h"

inline dword FIS_fwPutDevEvt(void)
{
  TRACEENTER();

  static dword          fwPutDevEvt = 0;

  if(!fwPutDevEvt)
    fwPutDevEvt = TryResolve("PutDevEvt");

  TRACEEXIT();
  return fwPutDevEvt;
}
