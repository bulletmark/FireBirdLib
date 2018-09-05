#include                <string.h>
#include                <stdlib.h>
#include                "libFireBird.h"
#include                "FBLib_LogoManager.h"

TYPE_GrData *LogoManager_GetLogoByChannelName(char *ChannelName, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR)
{
  TRACEENTER;

  char                  LogoName[FBLIB_DIR_SIZE];

  TYPE_GrData *ret = LogoManager_GetLogoByLogoName(LogoManager_ChannelNameToLogoName(ChannelName, LogoName, sizeof(LogoName)), LogoStyle, LogoSize, LogoAR);

  TRACEEXIT;
  return ret;
}
