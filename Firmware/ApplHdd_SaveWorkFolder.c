#include                "libFireBird.h"

void ApplHdd_SaveWorkFolder(void)
{
  TRACEENTER;

  void (*__ApplHdd_SaveWorkFolder)(void);

  __ApplHdd_SaveWorkFolder = (void*)FIS_fwApplHdd_SaveWorkFolder();
  if(__ApplHdd_SaveWorkFolder) __ApplHdd_SaveWorkFolder();

  TRACEEXIT;
}
