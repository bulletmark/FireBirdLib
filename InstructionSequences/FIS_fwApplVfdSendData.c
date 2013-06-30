#include "../libFireBird.h"

inline dword FIS_fwApplVfdSendData(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplVfdSendData");
  #endif

  static dword          ApplNewVfd_SendDatav = 0;

  if(!ApplNewVfd_SendDatav)
    ApplNewVfd_SendDatav = TryResolve("_Z19ApplNewVfd_SendDatav");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ApplNewVfd_SendDatav;
}
