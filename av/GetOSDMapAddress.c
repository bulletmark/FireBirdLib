#include "FBLib_av.h"
#include "../libFireBird.h"

dword GetOSDMapAddress(void)
{
  dword                ret;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("GetOSDMapAddress");
#endif

  ret = FIS_vOsdMap();

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

  return ret;
}
