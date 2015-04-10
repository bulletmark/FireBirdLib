#include                <stdlib.h>
#include                "FBLib_EPG.h"

#undef malloc
#undef free

void EPGInfo_Free(void)
{
  TRACEENTER();

  EPGInfo_DestroyCache();

  free(EPGFilter.GenreArray);
  memset(&EPGFilter, 0, sizeof(EPGFilter));

  TRACEEXIT();
}
