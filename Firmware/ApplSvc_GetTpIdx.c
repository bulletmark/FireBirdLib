#include                "libFireBird.h"

word ApplSvc_GetTpIdx(byte SatIndex, word NetworkID, word TSID)
{
  TRACEENTER;

  word (*__ApplSvc_GetTpIdx)(byte, word, word);
  word ret = 0xffff;

  __ApplSvc_GetTpIdx = (void*)FIS_fwApplSvc_GetTpIdx();
  if(__ApplSvc_GetTpIdx) ret = __ApplSvc_GetTpIdx(SatIndex, NetworkID, TSID);

  TRACEEXIT;
  return ret;
}
