#include                <string.h>
#include                "FBLib_debug.h"

void CallTraceExportStats(char *FileName)
{
  char                  Output[512];
  TYPE_File            *f;
  double                t;
  int                   i;

  if(!CallTraceInitialized) CallTraceInit();

  if(CallTraceStats && FileName)
  {
    if(TAP_Hdd_Exist(FileName)) TAP_Hdd_Delete(FileName);
    TAP_Hdd_Create(FileName, ATTR_NORMAL);
    f = TAP_Hdd_Fopen(FileName);
    if(f)
    {
      strcpy(Output, "Name;NrCalls;MinTime;MaxTime;TotalTime;AvgTime\r\n");
      TAP_Hdd_Fwrite(Output, strlen(Output), 1, f);

      for(i = 0; i < CallTraceStatsEntries;i++)
      {
        if(CallTraceStats[i].NrCalls)
          t = (double)(CallTraceStats[i].TotalTime * 10) / CallTraceStats[i].NrCalls;
        else
          t = 0;
        TAP_SPrint(Output, "%s;%d;%d;%d;%d;%1.1f\r\n", CallTraceStats[i].ProcName, CallTraceStats[i].NrCalls, CallTraceStats[i].MinTime*10, CallTraceStats[i].MaxTime*10, CallTraceStats[i].TotalTime*10, t);
        TAP_Hdd_Fwrite(Output, strlen(Output), 1, f);
      }
      TAP_Hdd_Fclose(f);
    }
  }
}
