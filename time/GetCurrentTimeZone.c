#include                "FBLib_time.h"

bool GetCurrentTimeZone(short *TZOffset, bool *DST)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetCurrentTimeZone");
  #endif

  //TZOffset receives the offset in minutes in the standard time zone
  //DST is set to TRUE if the Toppy is currently in DST mode

  tFlashTimeInfo        FlashTimeInfo;
  bool                  bDST;
  bool                  ret;

  ret = FALSE;
  if(FlashTimeGetInfo(&FlashTimeInfo))
  {
    bDST = (FlashTimeInfo.DST == 3);

    if(TZOffset)
    {
      *TZOffset = FlashTimeInfo.UTCOffset;
      if(bDST) *TZOffset = AddTime(*TZOffset, -60);
    }

    if(DST) *DST = bDST;

    ret = TRUE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
