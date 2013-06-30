#include                "FBLib_EPG.h"

void EPGInfo_FilterTime(dword StartTime, dword EndTime)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_FilterTime");
  #endif

  EPGFilter.StartTime = StartTime;
  EPGFilter.EndTime = EndTime;
  EPGFilter.TimeFilter = (StartTime || EndTime);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
