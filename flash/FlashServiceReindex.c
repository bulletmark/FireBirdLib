#include                <string.h>
#include                "FBLib_flash.h"

//Set FromSvcNum = -1 when adding a service entry
//or  ToSvcNum = -1 to deleting a service entry
void FlashReindexFavorites(int SvcType, int FromSvcNum, int ToSvcNum)
{
  tFavorites           *Favorites;
  int                   i, j;

  TRACEENTER();

  Favorites = (tFavorites*)FIS_vFlashBlockFavoriteGroup();

  for(i = 0; i < MAXFAVS; i++)
  {
    if(Favorites->GroupName[0] && Favorites->NrEntries)
    {
      j = 0;
      while(j < Favorites->NrEntries)
      {
        if(Favorites->SvcType[j] == SvcType)
        {
          if(FromSvcNum == -1)
          {
            //Case 1: a new service has been inserted at ToSvcNum
            if(Favorites->SvcNum[j] >= ToSvcNum) Favorites->SvcNum[j]++;
          }
          else if(ToSvcNum == -1)
          {
            //Case 2: a service has been deleted at FromSvcNum
            if(Favorites->SvcNum[j] >= FromSvcNum)
            {
              if(Favorites->SvcNum[j] == FromSvcNum)
              {
                memcpy(&Favorites->SvcNum[j], &Favorites->SvcNum[j + 1], (100 - j - 1) * sizeof(word));
                Favorites->SvcNum[99] = 0;
                Favorites->NrEntries--;
              }
              else
                Favorites->SvcNum[j]--;
            }
          }
          else if(FromSvcNum < ToSvcNum)
          {
            //Case 3: a service has been moved up
            if((Favorites->SvcNum[j] >= FromSvcNum) && (Favorites->SvcNum[j] <= ToSvcNum))
            {
              if(Favorites->SvcNum[j] == FromSvcNum)
                Favorites->SvcNum[j] = ToSvcNum;
              else
                Favorites->SvcNum[j]--;
            }
          }
          else
          {
            //Case 4: a service has been moved down
            if((Favorites->SvcNum[j] <= FromSvcNum) && (Favorites->SvcNum[j] >= ToSvcNum))
            {
              if(Favorites->SvcNum[j] == FromSvcNum)
                Favorites->SvcNum[j] = ToSvcNum;
              else
                Favorites->SvcNum[j]++;
            }
          }
        }
        j++;
      }
    }
    Favorites++;
  }

  TRACEEXIT();
}

void FlashReindexTimers(int SvcType, int FromSvcNum, int ToSvcNum)
{
  int                   NrTimer, i;
  TYPE_TimerInfo        TimerInfo;

  TRACEENTER();

  NrTimer = TAP_Timer_GetTotalNum();
  for(i = NrTimer - 1; i >= 0; i--)
  {
    TAP_Timer_GetInfo(i, &TimerInfo);
    if(TimerInfo.svcType == SvcType)
    {
      if(FromSvcNum == -1)
      {
        //Case 1: a new service has been inserted at ToSvcNum
        if(TimerInfo.svcNum >= ToSvcNum)
        {
          TimerInfo.svcNum++;
          TAP_Timer_Modify(i, &TimerInfo);
        }
      }
      else if(ToSvcNum == -1)
      {
        //Case 2: a service has been deleted at FromSvcNum
        if(TimerInfo.svcNum >= FromSvcNum)
        {
          if(TimerInfo.svcNum == FromSvcNum)
          {
            TAP_Timer_Delete(i);
          }
          else
          {
            TimerInfo.svcNum--;
            TAP_Timer_Modify(i, &TimerInfo);
          }
        }
      }
      else if(FromSvcNum < ToSvcNum)
      {
        //Case 3: a service has been moved up
        if((TimerInfo.svcNum >= FromSvcNum) && (TimerInfo.svcNum <= ToSvcNum))
        {
          if(TimerInfo.svcNum == FromSvcNum)
          {
            TimerInfo.svcNum = ToSvcNum;
            TAP_Timer_Modify(i, &TimerInfo);
          }
          else
          {
            TimerInfo.svcNum--;
            TAP_Timer_Modify(i, &TimerInfo);
          }
        }
      }
      else
      {
        //Case 4: a service has been moved down
        if((TimerInfo.svcNum <= FromSvcNum) && (TimerInfo.svcNum >= ToSvcNum))
        {
          if(TimerInfo.svcNum == FromSvcNum)
          {
            TimerInfo.svcNum = ToSvcNum;
            TAP_Timer_Modify(i, &TimerInfo);
          }
          else
          {
            TimerInfo.svcNum++;
            TAP_Timer_Modify(i, &TimerInfo);
          }
        }
      }
    }
  }

  TRACEEXIT();
}
