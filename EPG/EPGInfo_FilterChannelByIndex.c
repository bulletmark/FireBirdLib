#include                "FBLib_EPG.h"

void EPGInfo_FilterChannelByIndex(TYPE_ServiceType SvcType, int SvcNum, bool StartCurrent)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_FilterChannelByIndex");
  #endif

  TYPE_TapChInfo        chInfo;

  TAP_Channel_GetInfo(SvcType, SvcNum, &chInfo);

  EPGFilter.SatIndex = chInfo.satIdx;
  EPGFilter.NetworkID = chInfo.orgNetId;
  EPGFilter.TSID = chInfo.tsId;
  EPGFilter.ServiceID = chInfo.svcId;
  EPGFilter.StartCurrent = StartCurrent;

  EPGFilter.ChannelFilter = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
