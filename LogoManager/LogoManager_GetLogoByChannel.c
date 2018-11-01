#include                <string.h>
#include                <stdlib.h>
#include                "libFireBird.h"
#include                "FBLib_LogoManager.h"

TYPE_GrData *LogoManager_GetLogoByChannel(int SvcType, int SvcNum, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR)
{
  TRACEENTER();

  ulong64                 ChannelID;
  tFlashService           ServiceInfo;
  TYPE_GrData            *GrData;

  LogoManager_Initialize(LogoManager_CB);

  if(!FlashServiceGetInfo(SvcType, SvcNum, &ServiceInfo))
  {
    TRACEEXIT();
    return NULL;
  }

  //First retrieve by the channel name
  GrData = LogoManager_GetLogoByChannelName(ServiceInfo.ServiceName, LogoStyle, LogoSize, LogoAR);
  if(GrData)
  {
    TRACEEXIT();
    return GrData;
  }

  //Logo not available via channel name, now try it via the ID
  ChannelID =  LogoManager_GetChannelID(SvcType, SvcNum);
  GrData = LogoManager_GetLogoByChannelID(ChannelID, LogoStyle, LogoSize, LogoAR);

  TRACEEXIT();
  return GrData;
}
