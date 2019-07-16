#include "FBLib_flash.h"

bool FlashServiceFindNum(byte SatIndex, word NetworkID, word TSID, word ServiceID, TYPE_ServiceType *SvcType, int *SvcNum)
{
  TRACEENTER();

  word                    TpIdx, SvcIdx;
  bool                    ret;
  static byte             LastSatIndex = 0;
  static word             LastNetworkID = 0, LastTSID = 0, LastServiceID = 0;
  static TYPE_ServiceType LastSvcType = 0;
  static int              LastSvcNum = 0;
  int                     TrCount;
  tFlashTransponderTable  Transponder;

  if((SatIndex == LastSatIndex) && (NetworkID == LastNetworkID) && (TSID == LastTSID) && (ServiceID == LastServiceID))
  {
    if(SvcType) *SvcType = LastSvcType;
    if(SvcNum) *SvcNum = LastSvcNum;

    TRACEEXIT();
    return TRUE;
  }

  ret = FALSE;

  TrCount = FlashTransponderTablesGetTotal(SatIndex);
  for(TpIdx = 0; TpIdx < TrCount; TpIdx++)
  {
    if(FlashTransponderTablesGetInfo(SatIndex, TpIdx, &Transponder))
    {
      if((Transponder.OriginalNetworkID == NetworkID) && (Transponder.TSID == TSID))
      {
        SvcIdx = ApplSvc_GetSvcIdx(SVC_TYPE_Tv, SatIndex, TpIdx, ServiceID, 0, 0xffff);
        if(SvcIdx != 0xffff)
        {
          if(SvcType) *SvcType = SVC_TYPE_Tv;
          if(SvcNum) *SvcNum = SvcIdx;

          LastSatIndex = SatIndex;
          LastNetworkID = NetworkID;
          LastTSID = TSID;
          LastServiceID = ServiceID;
          LastSvcType = SVC_TYPE_Tv;
          LastSvcNum = SvcIdx;

          ret = TRUE;
          break;
        }
        else
        {
          SvcIdx = ApplSvc_GetSvcIdx(SVC_TYPE_Radio, SatIndex, TpIdx, ServiceID, 0, 0xffff);
          if(SvcIdx != 0xffff)
          {
            if(SvcType) *SvcType = SVC_TYPE_Radio;
            if(SvcNum) *SvcNum = SvcIdx;

            LastSatIndex = SatIndex;
            LastNetworkID = NetworkID;
            LastTSID = TSID;
            LastServiceID = ServiceID;
            LastSvcType = SVC_TYPE_Radio;
            LastSvcNum = SvcIdx;

            ret = TRUE;
            break;
          }
        }
      }
    }
  }

  TRACEEXIT();
  return ret;
}
