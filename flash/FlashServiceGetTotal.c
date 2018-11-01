#include                "libFireBird.h"

int FlashServiceGetTotal(int SvcType)
{
  TRACEENTER();

  int nTvSvc, nRadioSvc;

  TAP_Channel_GetTotalNum(&nTvSvc, &nRadioSvc);

  TRACEEXIT();
  return (SvcType == SVC_TYPE_Tv ? nTvSvc : nRadioSvc);
}
