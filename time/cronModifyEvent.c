#include                "FBLib_time.h"

extern TYPE_CRONTAB         cronTable[MAX_CRON_EVENTS];
extern bool                 cronInit;

bool cronModifyEvent(int Index, int frequency, dword nextExecution)
{
  TRACEENTER;

  if(!cronInit) cronUnregisterAllEvents();

  if((Index < 0) || (Index >= MAX_CRON_EVENTS) || !cronTable[Index].active)
  {
    TRACEEXIT;
    return FALSE;
  }

  cronTable[Index].frequency = frequency;
  cronTable[Index].nextExecution = nextExecution;

  TRACEEXIT;
  return TRUE;
}
