#include                "FBLib_debug.h"

void CallTraceExit(dword *Magic)
{
  char                  Spaces[101];
  int                   i, j;
  dword                 t;
  extern dword          __tap_ud__;

  if(CallTraceDoNotReenter) return;
  CallTraceDoNotReenter = TRUE;

  t = TAP_GetTick();

  if(!CallTraceInitialized) CallTraceInit();

  Spaces[0] = '\0';

  if(CallLevel > 0)
  {
    CallLevel--;

    if(CallTraceStats && CallLevel < CTSTACKSIZE)
    {
      //Check if the proc name is already known by the stats array
      j = -1;
      for(i = 0; i < CallTraceStatsEntries; i++)
        if(CallTraceStats[i].ProcName == CallTraceStack[CallLevel].ProcName)
        {
          j = i;
          break;
        }

      //If not, use the next free entry
      if(j == -1) j = CallTraceStatsEntries;

      //Add the stats
      if(j < CTSTATENTRIES)
      {
        i = t - CallTraceStack[CallLevel].EntryTime;
        if(CallTraceStats[j].ProcName)
        {
          //Already known
          if((dword)i < CallTraceStats[j].MinTime) CallTraceStats[j].MinTime = i;
          if((dword)i > CallTraceStats[j].MaxTime) CallTraceStats[j].MaxTime = i;
          CallTraceStats[j].TotalTime += i;
          if(CallTraceStats[j].NrCalls < 0xffffffff)
          {
            CallTraceStats[j].TotalTime += i;
            CallTraceStats[j].NrCalls++;
          }
        }
        else
        {
          //New procedure
          CallTraceStats[j].ProcName = CallTraceStack[CallLevel].ProcName;
          CallTraceStats[j].MinTime = i;
          CallTraceStats[j].MaxTime = i;
          CallTraceStats[j].TotalTime = i;
          CallTraceStats[j].NrCalls = 1;
          CallTraceStatsEntries++;
        }
      }
    }
  }
  else
    LogEntryFBLibPrintf(TRUE, "CallLevel Underflow! (TAPID 0x%8.8x)", __tap_ud__);

  if(CallTraceEnabled || Magic)
  {
    memset(Spaces, ' ', CallLevel < CTSTACKSIZE ? CallLevel << 1 : 100);
    Spaces[CallLevel < CTSTACKSIZE ? CallLevel << 1 : 100] = '\0';
  }

  if(Magic && *Magic != DEFAULTMAGIC)
  {
    TAP_PrintNet("%sINVALID MAGIC!\n", Spaces);
    *Magic = DEFAULTMAGIC;
  }

  CallTraceDoNotReenter = FALSE;
}
