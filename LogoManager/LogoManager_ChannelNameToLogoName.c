#include                <string.h>
#include                <stdlib.h>
#include                "libFireBird.h"
#include                "FBLib_LogoManager.h"

char *LogoManager_ChannelNameToLogoName(char *ChannelName, char *LogoName, int LogoNameSize)
{
  TRACEENTER;

  char                 *pLogoName;
  char                  AllowedChars[] = "abcdefghijklmnoprqstuvwxyz0123456789���+";

  if(LogoName && LogoNameSize)
  {
    memset(LogoName, 0, LogoNameSize);
    strncpy(LogoName, SkipCharTableBytes(ChannelName), LogoNameSize - 1);
    StrMkISO(LogoName);
    MakeValidFileName(LogoName, ControlChars | LFChars);
    LowerCase(LogoName);

    pLogoName = LogoName;
    while(*pLogoName)
    {
      if(index(AllowedChars, *pLogoName) == NULL)
        DeleteAt(pLogoName, 0, 1);
      else
        pLogoName++;
    }
    StrReplace(LogoName, "�", "ae");
    StrReplace(LogoName, "�", "oe");
    StrReplace(LogoName, "�", "ue");
  }

  TRACEEXIT;
  return LogoName;
}
