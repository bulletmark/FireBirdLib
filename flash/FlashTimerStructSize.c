#include                "../libFireBird.h"

int FlashTimerStructSize(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashTimerStructSize");
  #endif

  int ret = FIS_vTimerTempInfo() - FIS_vTimerEditInfo();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
