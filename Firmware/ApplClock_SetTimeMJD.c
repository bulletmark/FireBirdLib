#include                "libFireBird.h"

word ApplClock_SetTimeMJD(word mjd, byte hour, byte min, byte sec)
{
  TRACEENTER();

  word                  (*__ApplClock_SetTimeMJD)(word mjd, byte hour, byte min, byte sec);
  word                   ret = 0;

  __ApplClock_SetTimeMJD = (void*)FIS_fwApplClock_SetTimeMJD();
  if(__ApplClock_SetTimeMJD) ret = __ApplClock_SetTimeMJD(mjd, hour, min, sec);

  TRACEEXIT();
  return ret;
}
