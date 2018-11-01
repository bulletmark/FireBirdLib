#include                "libFireBird.h"

int FlashTimerStructSize(void)
{
  TRACEENTER();

  int ret = FIS_vTimerTempInfo() - FIS_vTimerEditInfo();

  TRACEEXIT();
  return ret;
}
