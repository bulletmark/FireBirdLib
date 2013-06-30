#include                "../libFireBird.h"

int ApplTap_GetEmptyTask(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ApplTap_GetEmptyTask");
  #endif

  int (*__ApplTap_GetEmptyTask)(void);
  int ret = 0;

  __ApplTap_GetEmptyTask = (void*)FIS_fwApplTap_GetEmptyTask();
  if(__ApplTap_GetEmptyTask) ret = __ApplTap_GetEmptyTask();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
