#include "../libFireBird.h"

inline dword FIS_fwApplChannel_GetAgc(void)
{
  static dword          _ApplChannel_GetAgc = 0;

  if(!_ApplChannel_GetAgc)
  {
    _ApplChannel_GetAgc = TryResolve("_Z18ApplChannel_GetAgchPh");
  }

  return _ApplChannel_GetAgc;
}
