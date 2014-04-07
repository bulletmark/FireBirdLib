#include "../libFireBird.h"

void FreeOSDRegion(word Region)
{
  TRACEENTER();

  tOSDMapInfo           *OSDMapInfo;

  if(!(OSDMapInfo = (tOSDMapInfo*) FIS_vOsdMap()))
  {
    TRACEEXIT();
    return;
  }

  if(OSDMapInfo[Region].pMemoryOSD) TAP_MemFree((void*)OSDMapInfo[Region].pMemoryOSD);

  memset(&OSDMapInfo[Region], 0, sizeof(tOSDMapInfo));

  TRACEEXIT();
}
