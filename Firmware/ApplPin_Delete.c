#include                "../libFireBird.h"

void ApplPin_Delete(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ApplPin_Delete");
  #endif

  void (*__ApplPin_Delete)(void);

  __ApplPin_Delete = (void*)FIS_fwApplPin_Delete();
  if(__ApplPin_Delete) __ApplPin_Delete();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
