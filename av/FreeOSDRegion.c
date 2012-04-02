#include "../libFireBird.h"

void FreeOSDRegion(word Region)
{
  tOSDMapInfo           *OSDMapInfo;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("FreeOSDRegion");
#endif


  if (!(OSDMapInfo = (tOSDMapInfo*) FIS_vOsdMap()))
  {

#ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
#endif

    return;
  }

  if (OSDMapInfo[Region].pMemoryOSD) TAP_MemFree((void *) OSDMapInfo[Region].pMemoryOSD);

  memset(&OSDMapInfo[Region], 0, sizeof(tOSDMapInfo));

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif
}
