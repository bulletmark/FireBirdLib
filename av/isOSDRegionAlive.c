#include "../libFireBird.h"

bool isOSDRegionAlive(word Region)
{
  bool                  ret;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("isOSDRegionAlive");
#endif

  ret = (GetOSDRegionWidth(Region) != 0 && GetOSDRegionHeight(Region) != 0);

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

  return ret;
}
