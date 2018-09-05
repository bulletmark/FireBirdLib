#include                <stdlib.h>
#include                "FBLib_EPG.h"

void EPGInfo_AbortLoad(void)
{
  TRACEENTER;

  EPGAbortLoad = TRUE;

  TRACEEXIT;
}
