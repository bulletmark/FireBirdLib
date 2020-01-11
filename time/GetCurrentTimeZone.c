#include                "FBLib_time.h"

bool GetCurrentTimeZone(short *TZOffset, bool *DST)
{
  TRACEENTER();

  //TZOffset receives the offset in minutes in the standard time zone
  //DST is set to TRUE if the Toppy is currently in DST mode

  tFlashTimeInfo        FlashTimeInfo;
  bool                  ret;

  ret = FALSE;
  if(FlashTimeGetInfo(&FlashTimeInfo))
  {
    if(TZOffset)
    {
      *TZOffset = FlashTimeInfo.UTCOffset;
      if(FlashTimeInfo.DSTActive) *TZOffset = AddTime(*TZOffset, -60);
    }

    if(DST) *DST = FlashTimeInfo.DSTActive;

    ret = TRUE;
  }

  TRACEEXIT();
  return ret;
}
