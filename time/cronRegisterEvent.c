#include                <stdlib.h>
#include                "FBLib_time.h"

extern int                  cronItemCount;
extern TYPE_CRONTAB         cronTable[MAX_CRON_EVENTS];
extern bool                 cronInit;

int cronRegisterEvent(long frequency, dword firstExecution, void *callback)
{
  TRACEENTER();

  bool                  ret;
  int                   i;
  TYPE_CRONTAB         *pcronTable;
  ret = -1;

  if(!cronInit) cronUnregisterAllEvents();

  if((cronItemCount < MAX_CRON_EVENTS) && (frequency) && (callback))
  {
    pcronTable = cronTable;
    for(i = 0; i <= MAX_CRON_EVENTS-1; i++)
    {
      if(!cronTable[i].active)
      {
        pcronTable->active = TRUE;
        pcronTable->function = callback;
        pcronTable->frequency = frequency;
        if(!firstExecution) firstExecution = TAP_GetTick() + abs(frequency);
        pcronTable->nextExecution = firstExecution;
        cronItemCount++;
        ret = i;
        break;
      }
      pcronTable++;
    }
  }

  TRACEEXIT();
  return ret;
}
