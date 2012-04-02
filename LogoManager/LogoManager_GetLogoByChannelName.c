#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

TYPE_GrData *LogoManager_GetLogoByChannelName(char *ChannelName, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR)
{
  return LogoManager_GetLogoByLogoName(LogoManager_ChannelNameToLogoName(ChannelName), LogoStyle, LogoSize, LogoAR);
}
