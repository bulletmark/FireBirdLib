#include                "../libFireBird.h"

int FlashServiceGetTotal(int SvcType)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashServiceGetTotal");
  #endif

  int nTvSvc, nRadioSvc;

  TAP_Channel_GetTotalNum(&nTvSvc, &nRadioSvc);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (SvcType == SVC_TYPE_Tv ? nTvSvc : nRadioSvc);
}
