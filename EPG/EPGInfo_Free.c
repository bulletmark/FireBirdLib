#include                <stdlib.h>
#include                "FBLib_EPG.h"

void EPGInfo_Free(void)
{
  TRACEENTER();

  EPGInfo_DestroyCache();

  TAP_MemFree(EPGFilter.GenreArray);
  memset(&EPGFilter, 0, sizeof(EPGFilter));

  TRACEEXIT();
}
