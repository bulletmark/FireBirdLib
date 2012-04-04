#include "../libFireBird.h"

word GetOSDRegionHeight(word Region)
{
  tOSDMapInfo          *OSDMapInfo;
  word                  ret;

#ifdef DEBUG_FIREBIRDLIB
  char buf[80];
  TAP_SPrint(buf, "GetOSDRegionHeight(%d)", Region);
  CallTraceEnter(buf);
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
  char buf[80];
  TAP_SPrint(buf, "%d", ret);
  CallTraceExitResult(NULL, buf);
#endif

  return ret;
}
