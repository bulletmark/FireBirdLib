#include                "EPG/FBLib_EPG.h"

void *Appl_GetSameTimeEvent(byte SatIndex, word NetID, word TSID, word ServiceID)
{
  TRACEENTER();

  dword                   CurrentGMT;
  dword                  *TreeByHashStart, *TreeByHashCurrent;
  TYPE_EvtInfo           *EventInfoCurrent;


  TreeByHashStart = Appl_GetEvtListHeadInHash(NetID, TSID, ServiceID);
  CurrentGMT = LocalTime2UTC(Now(NULL), NULL);
  TreeByHashCurrent = (dword*)*TreeByHashStart;
  if(TreeByHashCurrent != TreeByHashStart)
  {
    do
    {
      EventInfoCurrent = (TYPE_EvtInfo*)(TreeByHashCurrent - 8); //8 dwords == 0x20 bytes

      if((EventInfoCurrent->ServiceID == ServiceID) &&
         (EventInfoCurrent->TSID == TSID) &&
         (EventInfoCurrent->NetworkID == NetID) &&
         (EventInfoCurrent->SatIndex == SatIndex) &&
         ((EventInfoCurrent->DataStatus & 3) != 0) &&
         (EventInfoCurrent->StartTime <= CurrentGMT) &&
         (EventInfoCurrent->EndTime > CurrentGMT))
         {
           //Success
           TRACEEXIT();
           return EventInfoCurrent;
         }
      TreeByHashCurrent = (dword*)*TreeByHashCurrent;
    }while(TreeByHashCurrent != TreeByHashStart);
  }

  TRACEEXIT();
  return NULL;
}
