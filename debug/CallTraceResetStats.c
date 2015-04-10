#include                <stdlib.h>
#include                "FBLib_debug.h"

#undef malloc
#undef free

void CallTraceResetStats(void)
{
  if(!CallTraceInitialized) CallTraceInit();

  free(CallTraceStats);
  CallTraceStats = malloc(CTSTATENTRIES * sizeof(tCallTraceStats));
  if(CallTraceStats) memset(CallTraceStats, 0, CTSTATENTRIES * sizeof(tCallTraceStats));
  CallTraceStatsEntries = 0;
}
