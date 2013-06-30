#include "FBLib_av.h"
#include "../libFireBird.h"

dword GetOSDMapAddress(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetOSDMapAddress");
  #endif

  dword ret = FIS_vOsdMap();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
