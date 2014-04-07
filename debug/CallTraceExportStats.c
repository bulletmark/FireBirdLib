#include <fcntl.h>
#include <unistd.h>
#include                <string.h>
#include                "FBLib_debug.h"

void CallTraceExportStats(char *FileName)
{
  char                  Output[512];
  char                  AbsFileName[FBLIB_DIR_SIZE];
  int                   f;
  double                t;
  int                   i;

  if(!CallTraceInitialized) CallTraceInit();

  if(CallTraceStats && FileName)
  {
    ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);
    f = open(AbsFileName, O_WRONLY | O_CREAT | O_TRUNC);
    if(f >= 0)
    {
      strcpy(Output, "Name;NrCalls;MinTime;MaxTime;TotalTime;AvgTime\r\n");
      write(f, Output, strlen(Output));

      for(i = 0; i < CallTraceStatsEntries;i++)
      {
        if(CallTraceStats[i].NrCalls)
          t = (double)(CallTraceStats[i].TotalTime * 10) / CallTraceStats[i].NrCalls;
        else
          t = 0;
        TAP_SPrint(Output, "%s;%d;%d;%d;%d;%1.1f\r\n", CallTraceStats[i].ProcName, CallTraceStats[i].NrCalls, CallTraceStats[i].MinTime*10, CallTraceStats[i].MaxTime*10, CallTraceStats[i].TotalTime*10, t);
        write(f, Output, strlen(Output));
      }
      close(f);
    }
  }
}
