#include "../libFireBird.h"

inline dword FIS_fwApplHdd_GetInfoFromExternalDevice(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplHdd_GetInfoFromExternalDevice");
  #endif

  static dword          _ApplHdd_GetInfoFromExternalDevice = 0;

  if(!_ApplHdd_GetInfoFromExternalDevice)
    _ApplHdd_GetInfoFromExternalDevice = TryResolve("_Z33ApplHdd_GetInfoFromExternalDevicePjS_PKc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _ApplHdd_GetInfoFromExternalDevice;
}
