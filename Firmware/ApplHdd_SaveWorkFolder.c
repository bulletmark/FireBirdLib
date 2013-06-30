#include                "../libFireBird.h"

void ApplHdd_SaveWorkFolder(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ApplHdd_SaveWorkFolder");
  #endif

  void (*__ApplHdd_SaveWorkFolder)(void);

  __ApplHdd_SaveWorkFolder = (void*)FIS_fwApplHdd_SaveWorkFolder();
  if(__ApplHdd_SaveWorkFolder) __ApplHdd_SaveWorkFolder();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
