#include                "../libFireBird.h"

void ApplPin_Delete(void)
{
  TRACEENTER();

  void (*__ApplPin_Delete)(void);

  __ApplPin_Delete = (void*)FIS_fwApplPin_Delete();
  if(__ApplPin_Delete) __ApplPin_Delete();

  TRACEEXIT();
}
