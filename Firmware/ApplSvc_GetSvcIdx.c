#include                "libFireBird.h"

word ApplSvc_GetSvcIdx(byte TYPE_ServiceType, byte SatIndex, word TPIndex, word ServiceID, word Start, word NrOfServicesToSearch)
{
  TRACEENTER;

  word (*__ApplSvc_GetSvcIdx)(byte, byte, word, word, word, word);
  word ret = 0xffff;

  __ApplSvc_GetSvcIdx = (void*)FIS_fwApplSvc_GetSvcIdx();
  if(__ApplSvc_GetSvcIdx) ret = __ApplSvc_GetSvcIdx(TYPE_ServiceType, SatIndex, TPIndex, ServiceID, Start, NrOfServicesToSearch);

  TRACEEXIT;
  return ret;
}
