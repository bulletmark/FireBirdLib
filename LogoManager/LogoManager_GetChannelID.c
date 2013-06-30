#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

ulong64 LogoManager_GetChannelID(int SvcType, int SvcNum)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LogoManager_GetChannelID");
  #endif

  tFlashService           ServiceInfo;
  tFlashSatTable          SatInfo;
  tFlashTransponderTable  TransponderInfo;
  ulong64                 ChannelID;

  if(!FlashServiceGetInfo(SvcType, SvcNum, &ServiceInfo))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  if(!FlashSatTablesGetInfo(ServiceInfo.SatIndex, &SatInfo))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  if(!FlashTransponderTablesGetInfo(ServiceInfo.SatIndex, ServiceInfo.TransponderIndex, &TransponderInfo))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  ChannelID =  LogoManager_CalculateChannelID(SatInfo.SatPosition, TransponderInfo.OriginalNetworkID, TransponderInfo.TSID, ServiceInfo.ServiceID);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ChannelID;
}
