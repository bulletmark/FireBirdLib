#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

char *LogoManager_GetPathToLogoByChannelID(ulong64 ChannelID, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR)
{
  static char           LogoNameB[256];
  char                  s[20];

  LogoManager_Initialize(LogoManager_CB);

  TAP_SPrint(LogoNameB, "%s/", LogoManager_GetDirectory(LogoStyle, LogoAR));

  HDD_TAP_PushDir();
  HDD_ChangeDir(LOGOROOT);
  if(TAP_Hdd_Exist(LILNAME))
  {
    TAP_SPrint(s, "%16.16llx", ChannelID);
    INIOpenFile(LILNAME, NULL);
    INIGetString(s, &LogoNameB[strlen(LogoNameB)], "", 40);
    INICloseFile();
    HDD_TAP_PopDir();

    switch(LogoSize)
    {
      case LGSZ_qtl: strcat(LogoNameB, ".qtl"); break;
      case LGSZ_ibl: strcat(LogoNameB, ".ibl"); break;
      case LGSZ_qsl: strcat(LogoNameB, ".qsl"); break;
        default:
          break;
    }

    return LogoNameB;
  }
  HDD_TAP_PopDir();

  return "";
}
