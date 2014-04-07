#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

char *LogoManager_ChannelNameToLogoName(char *ChannelName)
{
  TRACEENTER();

  static char           LogoNameA[256];
  char                 *pLogoName;
  char                  AllowedChars[] = "abcdefghijklmnoprqstuvwxyz0123456789���+";

  memset(LogoNameA, 0, sizeof(LogoNameA));
  strncpy(LogoNameA, SkipCharTableBytes(ChannelName), sizeof(LogoNameA) - 1);
  StrMkISO(LogoNameA);
  MakeValidFileName(LogoNameA, ControlChars | LFChars);
  LowerCase(LogoNameA);

  pLogoName = LogoNameA;
  while(*pLogoName)
  {
    if(index(AllowedChars, *pLogoName) == NULL)
      DeleteAt(pLogoName, 0, 1);
    else
      pLogoName++;
  }
  StrReplace(LogoNameA, "�", "ae");
  StrReplace(LogoNameA, "�", "oe");
  StrReplace(LogoNameA, "�", "ue");

  TRACEEXIT();
  return LogoNameA;
}
