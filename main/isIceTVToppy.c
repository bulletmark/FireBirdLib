#include                "../libFireBird.h"

bool isIceTVToppy(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isIceTVToppy");
  #endif

  bool ret = FIS_fwApplIcelink_EitFromHdd() != 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
