#include                "../libFireBird.h"

dword ApplHdd_GetInfoFromExternalDevice(dword *TotalSpaceMB, dword *FreeSpaceMB, char  const *MountPath)
{
  dword                 (*__ApplHdd_GetInfoFromExternalDevice)(dword *, dword *, char  const *);
  dword                 ret = 0;

  __ApplHdd_GetInfoFromExternalDevice = (void*)FIS_fwApplHdd_GetInfoFromExternalDevice();
  if(__ApplHdd_GetInfoFromExternalDevice) ret = __ApplHdd_GetInfoFromExternalDevice(TotalSpaceMB, FreeSpaceMB, MountPath);

  return ret;
}
