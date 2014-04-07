#include                "../libFireBird.h"

dword ApplHdd_FreeSize(char *MountPath, bool a1)
{
  TRACEENTER();

  dword                 (*__ApplHdd_FreeSize)(char *, bool);
  dword                 ret = 0;

  __ApplHdd_FreeSize = (void*)FIS_fwApplHdd_SaveWorkFolder();
  if(__ApplHdd_FreeSize) ret = __ApplHdd_FreeSize(MountPath, a1);

  TRACEEXIT();
  return ret;
}
