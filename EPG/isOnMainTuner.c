#include                "FBLib_EPG.h"

bool isOnMainTuner(int SvcType, int SvcNum)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isOnMainTuner");
  #endif

  int                   svcTypeMainTuner, svcNumMainTuner;
  TYPE_TapChInfo        chInfo1, chInfo2;

  TAP_Channel_GetInfo(SvcType, SvcNum, &chInfo1);

  TAP_Channel_GetCurrent(&svcTypeMainTuner, &svcNumMainTuner);
  TAP_Channel_GetInfo(svcTypeMainTuner, svcNumMainTuner, &chInfo2);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (chInfo1.satIdx == chInfo2.satIdx) && (chInfo1.freq == chInfo2.freq);
}
