#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

TYPE_GrData *LogoManager_GetLogoByChannelName(char *ChannelName, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LogoManager_GetLogoByChannelName");
  #endif

  TYPE_GrData *ret = LogoManager_GetLogoByLogoName(LogoManager_ChannelNameToLogoName(ChannelName), LogoStyle, LogoSize, LogoAR);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
