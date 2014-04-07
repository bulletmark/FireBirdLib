#include                "../libFireBird.h"

void ApplNewVfd_Stop(void)
{
  TRACEENTER();

  void                  (*__ApplNewVfd_Stop)(void);

  __ApplNewVfd_Stop = (void*)FIS_fwApplVfdStop();
  if(__ApplNewVfd_Stop) __ApplNewVfd_Stop();

  TRACEEXIT();
}
