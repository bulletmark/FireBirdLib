#include "../libFireBird.h"

inline dword FIS_fwApplVfdStop(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplVfdStop");
  #endif

  static dword          ApplNewVfd_Stop = 0;

  if(!ApplNewVfd_Stop)
    ApplNewVfd_Stop = TryResolve("_Z15ApplNewVfd_Stopv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ApplNewVfd_Stop;
}
