#include "../libFireBird.h"

word GetOSDRegionWidth(word Region)
{
  TRACEENTER();

  tOSDMapInfo          *OSDMapInfo;
  word                  ret;

  if(!(OSDMapInfo = (tOSDMapInfo*) FIS_vOsdMap()))
  {
    TRACEEXIT();
    return 0;
  }

  ret = OSDMapInfo[Region].Width;

  TRACEEXIT();
  return ret;
}
