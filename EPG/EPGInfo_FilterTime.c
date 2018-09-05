#include                "FBLib_EPG.h"

void EPGInfo_FilterTime(dword StartTime, dword EndTime)
{
  TRACEENTER;

  EPGFilter.StartTime = StartTime;
  EPGFilter.EndTime = EndTime;
  EPGFilter.TimeFilter = (StartTime || EndTime);

  TRACEEXIT;
}
