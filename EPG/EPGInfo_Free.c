#include                "FBLib_EPG.h"

void EPGInfo_Free(void)
{
  TRACEENTER();

  EPGInfo_DestroyCache();

  if(EPGFilter.GenreArray) TAP_MemFree(EPGFilter.GenreArray);
  memset(&EPGFilter, 0, sizeof(EPGFilter));

  TRACEEXIT();
}
