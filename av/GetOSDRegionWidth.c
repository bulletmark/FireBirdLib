#include "../libFireBird.h"

word GetOSDRegionWidth(word Region)
{
  tOSDMapInfo          *OSDMapInfo;
  word                  ret;

#ifdef DEBUG_FIREBIRDLIB
  char buf[80];
  TAP_SPrint(buf, "GetOSDRegionWidth(%d)", Region);
  CallTraceEnter(buf);
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
  TAP_SPrint(buf, "%d", ret);
  CallTraceExitResult(NULL, buf);
#endif

  return ret;
}
