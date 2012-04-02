#include                "FBLib_debug.h"

void CallTraceEnter(char *ProcName)
{
  char                  Spaces[101];

  if(!CallTraceInitialized) CallTraceInit();

  if(CallLevel >= CTSTACKSIZE) TAP_Print("\n\nCallLevel Overflow!\n\n");
  if(CallTraceEnabled)
  {
    memset(Spaces, ' ', CallLevel < CTSTACKSIZE ? CallLevel << 1 : 100);
    Spaces[CallLevel < CTSTACKSIZE ? CallLevel << 1 : 100] = '\0';
    TAP_Print("%s%s\n", Spaces, ProcName);

    //Add the current routine to the stack
    if(CallLevel < CTSTACKSIZE)
    {
      CallTraceStack[CallLevel].ProcName = ProcName;
      CallTraceStack[CallLevel].EntryTime = TAP_GetTick();
    }
  }

  CallLevel++;
}
