#include                "FBLib_EPG.h"

void EPGInfo_FilterDuration(word MinDuration, word MaxDuration)
{
  TRACEENTER();

  if(MinDuration || MaxDuration)
  {
    EPGFilter.DurationFilter = TRUE;
    EPGFilter.MinDuration = MinDuration;
    EPGFilter.MaxDuration = MaxDuration;
  }
  else
  {
    EPGFilter.DurationFilter = FALSE;
    EPGFilter.MinDuration = 0;
    EPGFilter.MaxDuration = 0;
  }

  TRACEEXIT();
}
