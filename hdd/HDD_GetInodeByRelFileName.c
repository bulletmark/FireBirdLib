#include                <stdio.h>
#include                "../libFireBird.h"

dword HDD_GetInodeByRelFileName(char *FileName)
{
  char                  AbsFileName[256];

  if(!FileName) return 0;

  TAP_SPrint(AbsFileName, "%s%s", TAPFSROOT, FileName);

  return HDD_GetInodeByAbsFileName(AbsFileName);
}
