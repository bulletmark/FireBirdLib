#include                "FBLib_flash.h"

bool FlashServiceMove(int SvcType, int FromSvcNum, int ToSvcNum)
{
  int                   NrServices;
  tFlashService         Service, tempSvc;
  int                   i;

  NrServices = FlashServiceGetTotal(SvcType);

  //SvcType out of range
  if((SvcType < 0) || (SvcType > SVC_TYPE_Radio)) return FALSE;

  //SvcNum out of range
  if((FromSvcNum < 0) || (FromSvcNum >= NrServices) || (ToSvcNum < 0) || (ToSvcNum >= NrServices)) return FALSE;
  if(FromSvcNum == ToSvcNum) return TRUE;

  if(FromSvcNum < ToSvcNum)
  {
    //Case 3: a service has been moved up
    if(!FlashServiceGetInfo(SvcType, FromSvcNum, &Service)) return FALSE;

    for(i = FromSvcNum; i < ToSvcNum; i++)
    {
      FlashServiceGetInfo(SvcType, i + 1, &tempSvc);
      FlashServiceSetInfo(SvcType, i, &tempSvc);
    }
    FlashServiceSetInfo(SvcType, ToSvcNum, &Service);
  }
  else
  {
    //Case 4: a service has been moved down
    if(!FlashServiceGetInfo(SvcType, FromSvcNum, &Service)) return FALSE;

    for(i = FromSvcNum; i > ToSvcNum; i--)
    {
      FlashServiceGetInfo(SvcType, i - 1, &tempSvc);
      FlashServiceSetInfo(SvcType, i, &tempSvc);
    }
    FlashServiceSetInfo(SvcType, ToSvcNum, &Service);
  }

  FlashReindexFavorites(SvcType, FromSvcNum, ToSvcNum);
  FlashReindexTimers(SvcType, FromSvcNum, ToSvcNum);

  return TRUE;
}
