#include "libFireBird.h"

inline dword FIS_fwApplVfdStop(void)
{
  TRACEENTER();

  static dword          ApplNewVfd_Stop = 0;

  if(!ApplNewVfd_Stop)
    ApplNewVfd_Stop = TryResolve("_Z15ApplNewVfd_Stopv");

  TRACEEXIT();
  return ApplNewVfd_Stop;
}
