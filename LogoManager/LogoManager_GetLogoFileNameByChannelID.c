#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

char *LogoManager_GetPathToLogoByChannelID(ulong64 ChannelID, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR, char *LogoPath)
{
  TRACEENTER();

  char                  s[20], LP[FBLIB_DIR_SIZE];

  if(LogoPath)
  {
    LogoManager_Initialize(LogoManager_CB);

    TAP_SPrint(LogoPath, "%s/", LogoManager_GetDirectory(LogoStyle, LogoAR, LP));

    HDD_TAP_PushDir();
    HDD_ChangeDir(LOGOROOT);
    if(TAP_Hdd_Exist(LILNAME))
    {
      TAP_SPrint(s, "%16.16llx", ChannelID);
      INIOpenFile(LILNAME, NULL);
      INIGetString(s, &LogoPath[strlen(LogoPath)], "", 40);
      INICloseFile();
      HDD_TAP_PopDir();

      switch(LogoSize)
      {
        case LGSZ_qtl: strcat(LogoPath, ".qtl"); break;
        case LGSZ_ibl: strcat(LogoPath, ".ibl"); break;
        case LGSZ_qsl: strcat(LogoPath, ".qsl"); break;
          default:
            break;
      }

      TRACEEXIT();
      return LogoPath;
    }
    HDD_TAP_PopDir();
  }

  TRACEEXIT();
  return "";
}
