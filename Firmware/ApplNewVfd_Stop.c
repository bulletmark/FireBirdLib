#include                "../libFireBird.h"

void ApplNewVfd_Stop(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ApplNewVfd_Stop");
  #endif

  void                  (*__ApplNewVfd_Stop)(void);

  __ApplNewVfd_Stop = (void*)FIS_fwApplVfdStop();
  if(__ApplNewVfd_Stop) __ApplNewVfd_Stop();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
