#include                "libFireBird.h"

void ApplCiplus_CamSelect(byte CamIndex)
{
  TRACEENTER;

  void                  (*__ApplCiplus_CamSelect)(byte);

  __ApplCiplus_CamSelect = (void*)FIS_fwApplCiplus_CamSelect();
  if(__ApplCiplus_CamSelect) __ApplCiplus_CamSelect(CamIndex);

  TRACEEXIT;
}
