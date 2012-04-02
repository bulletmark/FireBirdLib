#include                "FBLib_debug.h"

void CallTraceResetStats(void)
{
  if(!CallTraceInitialized) CallTraceInit();

  if(CallTraceStats) TAP_MemFree(CallTraceStats);
  CallTraceStats = TAP_MemAlloc(CTSTATENTRIES * sizeof(tCallTraceStats));
  if(CallTraceStats) memset(CallTraceStats, 0, CTSTATENTRIES * sizeof(tCallTraceStats));
  CallTraceStatsEntries = 0;
}
