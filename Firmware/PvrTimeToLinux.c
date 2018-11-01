#include                "libFireBird.h"

dword PvrTimeToLinux(dword PVRTime)
{
  TRACEENTER();

  dword (*_PvrTimeToLinux)(dword) = NULL;
  dword ret;

  ret = 0xfe00;
  _PvrTimeToLinux = (void*)FIS_fwTimeToLinux();
  if(_PvrTimeToLinux) ret = _PvrTimeToLinux(PVRTime);

  TRACEEXIT();
  return ret;
}
