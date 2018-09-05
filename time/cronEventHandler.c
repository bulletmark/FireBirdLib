#include                "FBLib_time.h"

int                     cronItemCount = 0;
TYPE_CRONTAB            cronTable[MAX_CRON_EVENTS];
bool                    cronInit = FALSE;

void cronEventHandler(void)
{
  TRACEENTER;

  int                   i;
  long                  next;
  TYPE_CRONTAB         *pcronTable;

  if(!cronInit) cronUnregisterAllEvents();

  if(cronItemCount)
  {
    pcronTable = cronTable;
    for(i = 0; i <= MAX_CRON_EVENTS-1; i++)
    {
      if((pcronTable->active == TRUE) && (pcronTable->nextExecution <= TAP_GetTick()))
      {
        int (*theFunct)(void) = pcronTable->function;

        if(theFunct)
        {
          next = theFunct();
        }
        else
        {
          next = -1;
        }

        //If the callback function returns a -1 then deactivate that item
        //If frequency is < 0, this was a single-shot cron and also deactivate it
        if((next == -1) || (pcronTable->frequency < 0))
        {
          pcronTable->active = FALSE;
          cronItemCount--;
        }
        else
        {
          if(next == 0) next = pcronTable->frequency;      //If the callback returns zero, use the default frequency.
          do
          {
            pcronTable->nextExecution = pcronTable->nextExecution + next;
          } while(pcronTable->nextExecution < TAP_GetTick());
        }
      }
      pcronTable++;
    }
  }

  TRACEEXIT;
}
