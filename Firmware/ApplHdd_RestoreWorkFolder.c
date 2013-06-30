#include                "../libFireBird.h"

void ApplHdd_RestoreWorkFolder(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ApplHdd_RestoreWorkFolder");
  #endif

  void (*__ApplHdd_RestoreWorkFolder)(void);

  __ApplHdd_RestoreWorkFolder = (void*)FIS_fwApplHdd_RestoreWorkFolder();
  if(__ApplHdd_RestoreWorkFolder) __ApplHdd_RestoreWorkFolder();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
