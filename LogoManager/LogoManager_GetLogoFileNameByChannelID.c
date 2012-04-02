#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

char *LogoManager_GetPathToLogoByChannelID(ulong64 ChannelID, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR)
{
  static char           LogoName[256];
  char                  s[20];

  LogoManager_Initialize(LogoManager_CB);

  TAP_SPrint(LogoName, "%s/", LogoManager_GetDirectory(LogoStyle, LogoAR));

  HDD_TAP_PushDir();
  HDD_ChangeDir(LOGOROOT);
  if(TAP_Hdd_Exist(LILNAME))
  {
    TAP_SPrint(s, "%16.16llx", ChannelID);
    INIOpenFile(LILNAME, NULL);
    INIGetString(s, &LogoName[strlen(LogoName)], "", 40);
    INICloseFile();
    HDD_TAP_PopDir();

    switch(LogoSize)
    {
      case LGSZ_qtl: strcat(LogoName, ".qtl"); break;
      case LGSZ_ibl: strcat(LogoName, ".ibl"); break;
      case LGSZ_qsl: strcat(LogoName, ".qsl"); break;
        default:
          break;
    }

    return LogoName;
  }
  HDD_TAP_PopDir();

  return "";
}
