#include "libFireBird.h"

inline dword FIS_fwApplPin_Delete(void)
{
  TRACEENTER();

  static dword          _ApplPin_Delete = 0;

  if(!_ApplPin_Delete)
    _ApplPin_Delete = TryResolve("_Z14ApplPin_Deletev");

  TRACEEXIT();
  return _ApplPin_Delete;
}
