#include                "../libFireBird.h"

int ApplTap_GetEmptyTask(void)
{
  int (*__ApplTap_GetEmptyTask)(void);
  int ret = 0;

  __ApplTap_GetEmptyTask = (void*)FIS_fwApplTap_GetEmptyTask();
  if(__ApplTap_GetEmptyTask) ret = __ApplTap_GetEmptyTask();

  return ret;
}
