#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

ulong64 LogoManager_GetChannelID(int SvcType, int SvcNum)
{
  TRACEENTER();

  tFlashService           ServiceInfo;
  tFlashSatTable          SatInfo;
  tFlashTransponderTable  TransponderInfo;
  ulong64                 ChannelID;

  if(!FlashServiceGetInfo(SvcType, SvcNum, &ServiceInfo))
  {
    TRACEEXIT();
    return 0;
  }

  if(!FlashSatTablesGetInfo(ServiceInfo.SatIndex, &SatInfo))
  {
    TRACEEXIT();
    return 0;
  }

  if(!FlashTransponderTablesGetInfo(ServiceInfo.SatIndex, ServiceInfo.TransponderIndex, &TransponderInfo))
  {
    TRACEEXIT();
    return 0;
  }

  ChannelID =  LogoManager_CalculateChannelID(SatInfo.SatPosition, TransponderInfo.OriginalNetworkID, TransponderInfo.TSID, ServiceInfo.ServiceID);

  TRACEEXIT();
  return ChannelID;
}
