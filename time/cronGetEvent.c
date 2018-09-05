#include                "FBLib_time.h"

extern TYPE_CRONTAB         cronTable[MAX_CRON_EVENTS];
extern bool                 cronInit;

bool cronGetEvent(int Index, int *frequency, dword *nextExecution)
{
  TRACEENTER;

  if(!cronInit) cronUnregisterAllEvents();

  if((Index < 0) || (Index >= MAX_CRON_EVENTS) || !cronTable[Index].active)
  {
    TRACEEXIT;
    return FALSE;
  }

  if(frequency) *frequency = cronTable[Index].frequency;
  if(nextExecution) *nextExecution = cronTable[Index].nextExecution;

  TRACEEXIT;
  return TRUE;
}
