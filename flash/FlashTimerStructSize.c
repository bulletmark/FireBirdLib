#include                "../libFireBird.h"

int FlashTimerStructSize(void)
{
  return FIS_vTimerTempInfo() - FIS_vTimerEditInfo();
}
