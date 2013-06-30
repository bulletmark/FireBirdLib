#include "../libFireBird.h"

inline dword FIS_fwApplVfdStart(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplVfdStart");
  #endif

  static dword          ApplNewVfd_Start = 0;

  if(!ApplNewVfd_Start)
    ApplNewVfd_Start = TryResolve("_Z16ApplNewVfd_Startv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ApplNewVfd_Start;
}
