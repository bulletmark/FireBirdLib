#include "../libFireBird.h"

inline dword FIS_fwApplVfdSendData(void)
{
  static dword          ApplNewVfd_SendDatav = 0;

  if(!ApplNewVfd_SendDatav)
    ApplNewVfd_SendDatav = TryResolve("_Z19ApplNewVfd_SendDatav");

  return ApplNewVfd_SendDatav;
}
