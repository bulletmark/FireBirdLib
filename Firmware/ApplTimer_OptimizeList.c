#include                "../libFireBird.h"

void ApplTimer_OptimizeList(void)
{
  void                  (*__ApplTimer_OptimizeList)(void);

  __ApplTimer_OptimizeList = (void*)FIS_fwApplTimer_OptimizeList();
  if(__ApplTimer_OptimizeList) __ApplTimer_OptimizeList();
}
