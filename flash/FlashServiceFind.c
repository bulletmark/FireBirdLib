#include "FBLib_flash.h"

int FlashServiceFind(int SvcType, word ServiceID, word PMTPID, word PCRPID, tFlashService *Service)
{
  TRACEENTER();

  tFlashService         TempService;
  int                   i, NrChannels;

  NrChannels = FlashServiceGetTotal(SvcType);
  for(i = 0; i < NrChannels; i++)
  {
    if(!FlashServiceGetInfo(SvcType, i, &TempService)) return -1;

    if((TempService.ServiceID == ServiceID) && (TempService.PMTPID == PMTPID) && (TempService.PCRPID == PCRPID))
    {
      if(Service) memcpy(Service, &TempService, sizeof(tFlashService));

      TRACEEXIT();

      return i;
    }
  }

  TRACEEXIT();
  return -1;
}
