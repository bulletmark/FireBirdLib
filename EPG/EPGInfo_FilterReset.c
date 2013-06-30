#include                "FBLib_EPG.h"

void EPGInfo_FilterReset(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_FilterReset");
  #endif

  memset(&EPGFilter, 0, sizeof(EPGFilter));

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
