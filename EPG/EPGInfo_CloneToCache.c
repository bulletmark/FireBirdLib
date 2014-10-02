#include                <string.h>
#include                "FBLib_EPG.h"

void EPGInfo_CloneToCache(dword *TreePointer, byte StructOffset, tEPGFilter *EPGFilter)
{
  TRACEENTER();

  tTreeEntry           *ListStart, *Entry;
  TYPE_EvtInfo         *EvtInfo;
  int                   EvtInfoOffset;
  TYPE_EPGInfo         *CurrentCacheRecord;
  short                 Offset;
  dword                 EventStartTime, EventEndTime;
  bool                  isWithinTimeFrame, isValidChannel, isWithinDuration, isGenreOK;

  EPGInfoNrEntries = 0;
  CurrentCacheRecord = EPGInfoCache;
  EPGAbortLoad = FALSE;

  if(TreePointer)
  {
    EvtInfoOffset = StructOffset / sizeof(tTreeEntry);

    ListStart = (tTreeEntry*)*TreePointer;

    //If the list points to itself, no data is available
    if(ListStart == (tTreeEntry*)ListStart->Next)
    {
      TRACEEXIT();
      return;
    }

    //Loop until we're back at the beginning of the pool
    Entry = ListStart;
    do
    {
      EvtInfo = (TYPE_EvtInfo*)(Entry - EvtInfoOffset);

      if(FlashServiceFindNum(EvtInfo->SatIndex, EvtInfo->NetworkID, EvtInfo->TSID, EvtInfo->ServiceID, NULL, NULL))
      {
        if((dword)EvtInfo->TreeFull.Next != 0 && (dword)EvtInfo->TreeFull.Prev != 0)  //Only take events that are not scheduled for garbage collection
        {
          //Make the decisions, to add a pool record, here
          EventStartTime = UTC2LocalTime(EvtInfo->StartTime, &Offset);
          EventEndTime = UTC2LocalTime(EvtInfo->EndTime, NULL);
          if(EPGFilter->TimeFilter)
            isWithinTimeFrame = ((EPGFilter->StartTime == 0) || (EventStartTime >= EPGFilter->StartTime)) && ((EPGFilter->EndTime == 0) || (EventEndTime <= EPGFilter->EndTime));
          else
            isWithinTimeFrame = TRUE;


          if(EPGFilter->ChannelFilter)
            isValidChannel = (EvtInfo->SatIndex == EPGFilter->SatIndex) && (EvtInfo->NetworkID == EPGFilter->NetworkID) && (EvtInfo->TSID == EPGFilter->TSID) && (EvtInfo->ServiceID == EPGFilter->ServiceID);
          else
            isValidChannel = TRUE;


          if(EPGFilter->DurationFilter)
          {
            isWithinDuration = ((EPGFilter->MinDuration == 0) || (EvtInfo->durationHour * 60 + EvtInfo->durationMin >= EPGFilter->MinDuration)) &&
                ((EPGFilter->MaxDuration == 0) || (EvtInfo->durationHour * 60 + EvtInfo->durationMin <= EPGFilter->MaxDuration));
          }
          else
            isWithinDuration = TRUE;

          if(EPGFilter->GenreFilter)
          {
            byte *pGenre;
            int   i;

            //Loop through the genre array and check if there is a match
            isGenreOK = FALSE;
            pGenre = &EPGFilter->GenreArray[0];
            for(i = 0; i < EPGFilter->GenreArraySize; i++)
            {
              if(EvtInfo->ContentIdentifier == *pGenre)
              {
                isGenreOK = TRUE;
                break;
              }
              pGenre++;
            }
          }
          else
            isGenreOK = TRUE;

          //Call the Callback only if all other tests passed
          if(isWithinTimeFrame && isValidChannel && isWithinDuration && isGenreOK)
          {
            EPGInfo_CopyData(EvtInfo, CurrentCacheRecord, EventStartTime, EventEndTime, Offset);

            if(EPGFilter->UseCallback)
            {
              bool (*EPGFilterCallback)(TYPE_EPGInfo*) = EPGFilter->Callback;

              if(EPGFilterCallback(CurrentCacheRecord))
              {
                CurrentCacheRecord++;
                EPGInfoNrEntries++;
              }
            }
            else
            {
              CurrentCacheRecord++;
              EPGInfoNrEntries++;
            }
          }
        }//END test for garbage collection value
      }

      Entry = (tTreeEntry*)Entry->Next;
    } while(Entry && (Entry->Next != ListStart->Prev));
  }

  TRACEEXIT();
}
