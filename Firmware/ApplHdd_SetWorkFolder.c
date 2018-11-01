#include                "libFireBird.h"

void ApplHdd_SetWorkFolder(tDirEntry *FolderStruct)
{
  TRACEENTER();

  void (*__ApplHdd_SetWorkFolder)(void*);

  __ApplHdd_SetWorkFolder = (void*)FIS_fwApplHdd_SetWorkFolder();
  if(__ApplHdd_SetWorkFolder) __ApplHdd_SetWorkFolder(FolderStruct);

  TRACEEXIT();
}
