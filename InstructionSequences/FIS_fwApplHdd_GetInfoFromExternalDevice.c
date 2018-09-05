#include "libFireBird.h"

inline dword FIS_fwApplHdd_GetInfoFromExternalDevice(void)
{
  TRACEENTER;

  static dword          _ApplHdd_GetInfoFromExternalDevice = 0;

  if(!_ApplHdd_GetInfoFromExternalDevice)
    _ApplHdd_GetInfoFromExternalDevice = TryResolve("_Z33ApplHdd_GetInfoFromExternalDevicePjS_PKc");

  TRACEEXIT;
  return _ApplHdd_GetInfoFromExternalDevice;
}
