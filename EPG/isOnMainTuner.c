#include                "FBLib_EPG.h"

bool isOnMainTuner(int SvcType, int SvcNum)
{
  TRACEENTER;

  int                   svcTypeMainTuner, svcNumMainTuner;
  TYPE_TapChInfo        chInfo1, chInfo2;

  TAP_Channel_GetInfo(SvcType, SvcNum, &chInfo1);

  TAP_Channel_GetCurrent(&svcTypeMainTuner, &svcNumMainTuner);
  TAP_Channel_GetInfo(svcTypeMainTuner, svcNumMainTuner, &chInfo2);

  TRACEEXIT;
  return (chInfo1.satIdx == chInfo2.satIdx) && (chInfo1.freq == chInfo2.freq);
}
