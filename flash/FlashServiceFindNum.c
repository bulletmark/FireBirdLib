#include "FBLib_flash.h"

bool FlashServiceFindNum(byte SatIndex, word NetworkID, word TSID, word ServiceID, TYPE_ServiceType *SvcType, int *SvcNum)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashServiceFindNum");
  #endif

  word TpIdx;
  word SvcIdx;
  bool ret;

  ret = FALSE;

  TpIdx = ApplSvc_GetTpIdx(SatIndex, NetworkID, TSID);
  if(TpIdx != 0xffff)
  {
    SvcIdx = ApplSvc_GetSvcIdx(SVC_TYPE_Tv, SatIndex, TpIdx, ServiceID, 0, 0xffff);
    if(SvcIdx != 0xffff)
    {
      if(SvcType) *SvcType = SVC_TYPE_Tv;
      if(SvcNum) *SvcNum = SvcIdx;
      ret = TRUE;
    }
    else
    {
      SvcIdx = ApplSvc_GetSvcIdx(SVC_TYPE_Radio, SatIndex, TpIdx, ServiceID, 0, 0xffff);
      if(SvcIdx != 0xffff)
      {
        if(SvcType) *SvcType = SVC_TYPE_Radio;
        if(SvcNum) *SvcNum = SvcIdx;
        ret = TRUE;
      }
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
