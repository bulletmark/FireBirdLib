#include                "libFireBird.h"

dword ApplHdd_GetInfoFromExternalDevice(dword *TotalSpaceMB, dword *FreeSpaceMB, char *MountPath)
{
  TRACEENTER;

  dword                 (*__ApplHdd_GetInfoFromExternalDevice)(dword *, dword *, char *);
  dword                 ret = 0;

  __ApplHdd_GetInfoFromExternalDevice = (void*)FIS_fwApplHdd_GetInfoFromExternalDevice();
  if(__ApplHdd_GetInfoFromExternalDevice) ret = __ApplHdd_GetInfoFromExternalDevice(TotalSpaceMB, FreeSpaceMB, MountPath);

  TRACEEXIT;
  return ret;
}
