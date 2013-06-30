#include "../libFireBird.h"

word GetOSDRegionWidth(word Region)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetOSDRegionWidth");
  #endif

  tOSDMapInfo          *OSDMapInfo;
  word                  ret;

  if(!(OSDMapInfo = (tOSDMapInfo*) FIS_vOsdMap()))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  ret = OSDMapInfo[Region].Width;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
