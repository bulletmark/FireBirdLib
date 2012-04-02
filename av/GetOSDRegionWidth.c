#include "../libFireBird.h"

word GetOSDRegionWidth(word Region)
{
  tOSDMapInfo          *OSDMapInfo;
  word                  ret;

#ifdef DEBUG_FIREBIRDLIB
  TAP_SPrint(tracePuffer, "GetOSDRegionWidth(%d)", Region);
  CallTraceEnter(tracePuffer);
#endif

  if (!(OSDMapInfo = (tOSDMapInfo*) FIS_vOsdMap()))
  {

#ifdef DEBUG_FIREBIRDLIB
    CallTraceExitResult(NULL, "0");
#endif

    return 0;
  }

  ret = OSDMapInfo[Region].Width;

#ifdef DEBUG_FIREBIRDLIB
  TAP_SPrint(tracePuffer, "%d", ret);
  CallTraceExitResult(NULL, tracePuffer);
#endif

  return ret;
}
