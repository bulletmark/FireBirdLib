#include "libFireBird.h"

inline dword FIS_fwApplCiplus_GetSelectedCam(void)
{
  TRACEENTER();

  static dword          _ApplCiplus_GetSelectedCam = 0;

  if(!_ApplCiplus_GetSelectedCam)
    _ApplCiplus_GetSelectedCam = TryResolve("_Z25ApplCiplus_GetSelectedCamv");

  TRACEEXIT();
  return _ApplCiplus_GetSelectedCam;
}
