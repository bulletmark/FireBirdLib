#include                "FBLib_debug.h"

dword                   CallLevel        = 0;
tCallTraceStack         CallTraceStack[CTSTACKSIZE];
bool                    CallTraceEnabled = FALSE;
bool                    CallTraceInitialized = FALSE;
tCallTraceStats        *CallTraceStats = NULL;
int                     CallTraceStatsEntries = 0;

void CallTraceInit(void)
{
  CallLevel = 0;
  CallTraceEnabled = TRUE;
  CallTraceInitialized = TRUE;
  CallTraceResetStats();

  memset(CallTraceStack, 0, CTSTACKSIZE * sizeof(tCallTraceStack));
}
