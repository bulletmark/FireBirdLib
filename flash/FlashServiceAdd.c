#include                "FBLib_flash.h"

bool FlashServiceAdd(int SvcType, tFlashService *Service)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashServiceAdd");
  #endif

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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
