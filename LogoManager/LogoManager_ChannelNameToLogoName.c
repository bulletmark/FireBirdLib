#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

char *LogoManager_ChannelNameToLogoName(char *ChannelName)
{
  static char           LogoName[512];
  char                 *pLogoName;
  char                  AllowedChars[] = "abcdefghijklmnoprqstuvwxyz0123456789הצü+";

  memset(LogoName, 0, sizeof(LogoName));
  strncpy(LogoName, ChannelName, 255);
  LowerCase(LogoName);
  pLogoName = LogoName;
  while(*pLogoName)
  {
    if(index(AllowedChars, *pLogoName) == NULL)
      DeleteAt(pLogoName, 0, 1);
    else
      pLogoName++;
  }
  StrReplace(LogoName, "ה", "ae");
  StrReplace(LogoName, "צ", "oe");
  StrReplace(LogoName, "ü", "ue");

  return LogoName;
}
