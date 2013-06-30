#include                "../libFireBird.h"

dword ApplHdd_GetInfoFromExternalDevice(dword *TotalSpaceMB, dword *FreeSpaceMB, char *MountPath)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ApplHdd_GetInfoFromExternalDevice");
  #endif

  dword                 (*__ApplHdd_GetInfoFromExternalDevice)(dword *, dword *, char *);
  dword                 ret = 0;

  __ApplHdd_GetInfoFromExternalDevice = (void*)FIS_fwApplHdd_GetInfoFromExternalDevice();
  if(__ApplHdd_GetInfoFromExternalDevice) ret = __ApplHdd_GetInfoFromExternalDevice(TotalSpaceMB, FreeSpaceMB, MountPath);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
