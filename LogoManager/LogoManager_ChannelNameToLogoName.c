#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

char *LogoManager_ChannelNameToLogoName(char *ChannelName)
{
  static char           LogoNameA[256];
  char                 *pLogoName;
  char                  AllowedChars[] = "abcdefghijklmnoprqstuvwxyz0123456789הצü+";

  memset(LogoNameA, 0, sizeof(LogoNameA));
  strncpy(LogoNameA, ChannelName, 255);
  LowerCase(LogoNameA);
  pLogoName = LogoNameA;
  while(*pLogoName)
  {
    if(index(AllowedChars, *pLogoName) == NULL)
      DeleteAt(pLogoName, 0, 1);
    else
      pLogoName++;
  }
  StrReplace(LogoNameA, "ה", "ae");
  StrReplace(LogoNameA, "צ", "oe");
  StrReplace(LogoNameA, "ü", "ue");

  return LogoNameA;
}
