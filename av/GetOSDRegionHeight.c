#include "../libFireBird.h"

word GetOSDRegionHeight(word Region)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetOSDRegionHeight");
  #endif

  tOSDMapInfo          *OSDMapInfo;
  word                  ret;

  OSDMapInfo = (tOSDMapInfo*) FIS_vOsdMap();

  if(!OSDMapInfo)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  ret = OSDMapInfo[Region].Height;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
