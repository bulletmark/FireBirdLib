#include                "../libFireBird.h"

dword ApplHdd_SelectFolder(tDirEntry *FolderStruct, char const *FolderPath)
{
  dword                 (*__ApplHdd_SelectFolder)(tDirEntry *FolderStruct, char const *FolderPath);
  dword                 ret = 0;

  __ApplHdd_SelectFolder = (void*)FIS_fwApplHdd_SelectFolder();
  if(__ApplHdd_SelectFolder) ret = __ApplHdd_SelectFolder(FolderStruct, FolderPath);

  return ret;
}
