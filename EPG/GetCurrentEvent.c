#include "../libFireBird.h"

TYPE_TapEvent *GetCurrentEvent(int *nCurEvent)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetCurrentEvent");
  #endif

  TYPE_TapEvent         *evtInfo;
  unsigned int          eventNum, i;
  int                   svcType, svcNum;

  TAP_Channel_GetCurrent(&svcType, &svcNum);
  evtInfo = TAP_GetEvent(svcType, svcNum, &eventNum);

  if(evtInfo)
  {
    for(i = 0; i < eventNum; i++)
    {
      if(evtInfo[i].runningStatus == 4)
      {
        if(nCurEvent) *nCurEvent = i;
        return evtInfo;
      }
    }
  }

  if(evtInfo) TAP_MemFree(evtInfo);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return NULL;
}
