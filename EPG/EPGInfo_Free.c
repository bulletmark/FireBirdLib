#include                "FBLib_EPG.h"

void EPGInfo_Free(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_Free");
  #endif

  EPGInfo_DestroyCache();

  if(EPGFilter.GenreArray) TAP_MemFree(EPGFilter.GenreArray);
  memset(&EPGFilter, 0, sizeof(EPGFilter));

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
