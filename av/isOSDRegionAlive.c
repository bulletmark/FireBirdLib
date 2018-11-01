#include "libFireBird.h"

bool isOSDRegionAlive(word Region)
{
  TRACEENTER();

  bool ret = (GetOSDRegionWidth(Region) != 0 && GetOSDRegionHeight(Region) != 0);

  TRACEEXIT();
  return ret;
}
