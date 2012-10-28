#include                "../libFireBird.h"

bool isIceTVToppy(void)
{
  return FIS_fwApplIcelink_EitFromHdd() != 0;
}
