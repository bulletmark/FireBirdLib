#include                "libFireBird.h"

bool isIceTVToppy(void)
{
  TRACEENTER();

  bool ret = FIS_fwApplIcelink_EitFromHdd() != 0;

  TRACEEXIT();
  return ret;
}
