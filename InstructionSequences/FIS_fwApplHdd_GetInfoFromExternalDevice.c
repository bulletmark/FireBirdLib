#include "../libFireBird.h"

inline dword FIS_fwApplHdd_GetInfoFromExternalDevice(void)
{
  static dword          _ApplHdd_GetInfoFromExternalDevice = 0;

  if(!_ApplHdd_GetInfoFromExternalDevice) _ApplHdd_GetInfoFromExternalDevice = TryResolve("_Z33ApplHdd_GetInfoFromExternalDevicePjS_PKc");

  return _ApplHdd_GetInfoFromExternalDevice;
}
