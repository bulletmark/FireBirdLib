#include                "../libFireBird.h"

int FlashServiceGetTotal(int SvcType)
{
  int nTvSvc, nRadioSvc;

  TAP_Channel_GetTotalNum(&nTvSvc, &nRadioSvc);

  return (SvcType == SVC_TYPE_Tv ? nTvSvc : nRadioSvc);
}
