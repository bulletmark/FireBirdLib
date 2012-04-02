#include                "FBLib_flash.h"

bool FlashServiceAdd(int SvcType, tFlashService *Service)
{
  int                   NrServices;
  word                 *nSvc;

  NrServices = FlashServiceGetTotal(SvcType);

  if(SvcType == SVC_TYPE_Tv)
    nSvc = (word*)FIS_vnTvSvc();
  else
    nSvc = (word*)FIS_vnRadioSvc();

  *nSvc = *nSvc + 1;

  return FlashServiceSetInfo(SvcType, NrServices, Service);
}
