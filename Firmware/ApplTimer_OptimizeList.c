#include                "../libFireBird.h"

void ApplTimer_OptimizeList(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ApplTimer_OptimizeList");
  #endif

  void                  (*__ApplTimer_OptimizeList)(void);

  __ApplTimer_OptimizeList = (void*)FIS_fwApplTimer_OptimizeList();
  if(__ApplTimer_OptimizeList) __ApplTimer_OptimizeList();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
