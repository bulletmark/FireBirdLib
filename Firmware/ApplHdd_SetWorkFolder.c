#include                "../libFireBird.h"

void ApplHdd_SetWorkFolder(tDirEntry *FolderStruct)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ApplHdd_SetWorkFolder");
  #endif

  void (*__ApplHdd_SetWorkFolder)(void*);

  __ApplHdd_SetWorkFolder = (void*)FIS_fwApplHdd_SetWorkFolder();
  if(__ApplHdd_SetWorkFolder) __ApplHdd_SetWorkFolder(FolderStruct);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
