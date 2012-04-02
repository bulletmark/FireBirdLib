#include                "../libFireBird.h"

dword Appl_GetFreeExtRecordSpace(char *MountPath)
{
  dword                 (*__Appl_GetFreeExtRecordSpace)(char *);
  dword                 ret = 0;

  __Appl_GetFreeExtRecordSpace = (void*)FIS_fwAppl_GetFreeExtRecordSpace();
  if(__Appl_GetFreeExtRecordSpace) ret = __Appl_GetFreeExtRecordSpace(MountPath);

  return ret;
}
