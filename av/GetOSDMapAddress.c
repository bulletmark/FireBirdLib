#include "FBLib_av.h"
#include "libFireBird.h"

dword GetOSDMapAddress(void)
{
  TRACEENTER;

  dword ret = FIS_vOsdMap();

  TRACEEXIT;
  return ret;
}
