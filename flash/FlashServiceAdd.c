#include                "FBLib_flash.h"

bool FlashServiceAdd(int SvcType, tFlashService *Service)
{
  TRACEENTER();

  int                   NrServices;
  word                 *nSvc;
  bool                  ret;

  NrServices = FlashServiceGetTotal(SvcType);

  if(SvcType == SVC_TYPE_Tv)
    nSvc = (word*)FIS_vnTvSvc();
  else
    nSvc = (word*)FIS_vnRadioSvc();

  *nSvc = *nSvc + 1;
  ret = FlashServiceSetInfo(SvcType, NrServices, Service);

  TRACEEXIT();
  return ret;
}
