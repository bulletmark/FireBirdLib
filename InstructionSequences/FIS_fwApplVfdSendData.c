#include "libFireBird.h"

inline dword FIS_fwApplVfdSendData(void)
{
  TRACEENTER;

  static dword          ApplNewVfd_SendDatav = 0;

  if(!ApplNewVfd_SendDatav)
    ApplNewVfd_SendDatav = TryResolve("_Z19ApplNewVfd_SendDatav");

  TRACEEXIT;
  return ApplNewVfd_SendDatav;
}
