#include                "FBLib_tmsvfd.h"

bool VFD_isInUseByTAP(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("VFD_isInUseByTAP");
  #endif

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return VFDUsedByTAP;
}
