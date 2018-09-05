#include                "FBLib_time.h"

extern int                  cronItemCount;
extern TYPE_CRONTAB         cronTable[MAX_CRON_EVENTS];
extern bool                 cronInit;

bool cronUnregisterEvent(int Index)
{
  TRACEENTER;

  bool                  ret = FALSE;

  if(!cronInit) cronUnregisterAllEvents();

  if((cronItemCount > 0) && (Index >= 0) && (Index < MAX_CRON_EVENTS))
  {
    if(cronTable[Index].active)
    {
      cronTable[Index].active = FALSE;
      cronItemCount--;
      ret = TRUE;
    }
  }

  TRACEEXIT;
  return ret;
}
