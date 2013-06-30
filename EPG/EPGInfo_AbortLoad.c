#include                <stdlib.h>
#include                "FBLib_EPG.h"

void EPGInfo_AbortLoad(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_AbortLoad");
  #endif

  EPGAbortLoad = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
