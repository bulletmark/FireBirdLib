#include "libFireBird.h"

word GetOSDRegionHeight(word Region)
{
  TRACEENTER;

  tOSDMapInfo          *OSDMapInfo;
  word                  ret;

  OSDMapInfo = (tOSDMapInfo*) FIS_vOsdMap();

  if(!OSDMapInfo)
  {
    TRACEEXIT;
    return 0;
  }

  ret = OSDMapInfo[Region].Height;

  TRACEEXIT;
  return ret;
}
