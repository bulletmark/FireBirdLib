#include "../libFireBird.h"

word GetOSDRegionHeight(word Region)
{
  tOSDMapInfo          *OSDMapInfo;
  word                  ret;

#ifdef DEBUG_FIREBIRDLIB
  TAP_SPrint(tracePuffer, "GetOSDRegionHeight(%d)", Region);
  CallTraceEnter(tracePuffer);
#endif

  OSDMapInfo = (tOSDMapInfo*) FIS_vOsdMap();

  if (!OSDMapInfo)
  {

#ifdef DEBUG_FIREBIRDLIB
    CallTraceExitResult(NULL, "0");
#endif

    return 0;
  }

  ret = OSDMapInfo[Region].Height;

#ifdef DEBUG_FIREBIRDLIB
  TAP_SPrint(tracePuffer, "%d", ret);
  CallTraceExitResult(NULL, tracePuffer);
#endif

  return ret;
}
