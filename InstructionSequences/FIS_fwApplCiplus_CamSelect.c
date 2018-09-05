#include "libFireBird.h"

inline dword FIS_fwApplCiplus_CamSelect(void)
{
  TRACEENTER;

  static dword          _ApplCiplus_CamSelect = 0;

  if(!_ApplCiplus_CamSelect)
    _ApplCiplus_CamSelect = TryResolve("_Z20ApplCiplus_CamSelecth");

  TRACEEXIT;
  return _ApplCiplus_CamSelect;
}
