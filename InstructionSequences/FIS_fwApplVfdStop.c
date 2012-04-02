#include "../libFireBird.h"

inline dword FIS_fwApplVfdStop(void)
{
  static dword          ApplNewVfd_Stop = 0;

  if(!ApplNewVfd_Stop)
    ApplNewVfd_Stop = TryResolve("_Z15ApplNewVfd_Stopv");

  return ApplNewVfd_Stop;
}
