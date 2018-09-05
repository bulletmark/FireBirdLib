#include                "libFireBird.h"

byte ApplCiplus_GetSelectedCam(void)
{
  TRACEENTER;

  byte                  (*__ApplCiplus_GetSelectedCam)(void);
  byte                  ret = 0;

  __ApplCiplus_GetSelectedCam = (void*)FIS_fwApplCiplus_GetSelectedCam();
  if(__ApplCiplus_GetSelectedCam) ret = __ApplCiplus_GetSelectedCam();

  TRACEEXIT;
  return ret;
}
