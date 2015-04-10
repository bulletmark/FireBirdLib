#include                <stdlib.h>
#include                "FBLib_debug.h"

#undef malloc
#undef free

void CallTraceEnter(char *ProcName)
{
  char                  Spaces[101];
  byte                 *ISOText;
  extern dword          __tap_ud__;

  if(CallTraceDoNotReenter) return;
  CallTraceDoNotReenter = TRUE;

  if(!CallTraceInitialized) CallTraceInit();

  if(CallLevel >= CTSTACKSIZE) LogEntryFBLibPrintf(TRUE, "CallLevel Overflow! (TAPID 0x%8.8x)", __tap_ud__);

  if(ProcName)
  {
    if(CallTraceEnabled)
    {
      StrToISOAlloc(ProcName, &ISOText);
      memset(Spaces, ' ', CallLevel < CTSTACKSIZE ? CallLevel << 1 : 100);
      Spaces[CallLevel < CTSTACKSIZE ? CallLevel << 1 : 100] = '\0';
      TAP_PrintNet("%s%s\n", Spaces, ISOText);
      free(ISOText);
    }

    //Add the current routine to the stack
    if(CallLevel < CTSTACKSIZE)
    {
      CallTraceStack[CallLevel].ProcName = ProcName;
      CallTraceStack[CallLevel].EntryTime = TAP_GetTick();
    }
  }

  CallLevel++;
  CallTraceDoNotReenter = FALSE;
}
