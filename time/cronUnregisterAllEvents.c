#include                "FBLib_time.h"

extern int                  cronItemCount;
extern TYPE_CRONTAB         cronTable[MAX_CRON_EVENTS];
extern bool                 cronInit;

void cronUnregisterAllEvents(void)
{
  TRACEENTER();

  memset(cronTable, 0, MAX_CRON_EVENTS * sizeof(TYPE_CRONTAB));
  cronItemCount = 0;
  cronInit = TRUE;

  TRACEEXIT();
}
