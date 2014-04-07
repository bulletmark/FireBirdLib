#include                "FBLib_EPG.h"

void EPGInfo_FilterReset(void)
{
  TRACEENTER();

  memset(&EPGFilter, 0, sizeof(EPGFilter));

  TRACEEXIT();
}
