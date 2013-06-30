#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

TYPE_GrData *LogoManager_GetLogoByChannel(int SvcType, int SvcNum, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LogoManager_GetLogoByChannel");
  #endif

  ulong64                 ChannelID;
  tFlashService           ServiceInfo;
  TYPE_GrData            *GrData;

  LogoManager_Initialize(LogoManager_CB);

  if(!FlashServiceGetInfo(SvcType, SvcNum, &ServiceInfo))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  //First retrieve by the channel name
  GrData = LogoManager_GetLogoByChannelName(ServiceInfo.ServiceName, LogoStyle, LogoSize, LogoAR);
  if(GrData)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return GrData;
  }

  //Logo not available via channel name, now try it via the ID
  ChannelID =  LogoManager_GetChannelID(SvcType, SvcNum);
  GrData = LogoManager_GetLogoByChannelID(ChannelID, LogoStyle, LogoSize, LogoAR);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return GrData;
}
