#include <stdlib.h>
#include "../libFireBird.h"

#undef malloc
#undef free

void FreeOSDRegion(word Region)
{
  TRACEENTER();

  tOSDMapInfo           *OSDMapInfo;

  if(!(OSDMapInfo = (tOSDMapInfo*) FIS_vOsdMap()))
  {
    TRACEEXIT();
    return;
  }

  free((void*)OSDMapInfo[Region].pMemoryOSD);
  memset(&OSDMapInfo[Region], 0, sizeof(tOSDMapInfo));

  TRACEEXIT();
}
