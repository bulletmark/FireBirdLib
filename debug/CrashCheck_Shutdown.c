#include                "FBLib_debug.h"

void CrashCheck_Shutdown(char *TAPName)
{
  TRACEENTER;

  INILOCATION           INILocation;

  if(TAPName)
  {
    HDD_TAP_PushDir();
    HDD_ChangeDir("/ProgramFiles/Settings");

    INILocation = INIOpenFile(CRASHCHECKINI, NULL);
    INISetInt(TAPName, 0);
    if(INILocation == INILOCATION_NewFile) INILocation = INILOCATION_AtSettings;
    INISaveFile(CRASHCHECKINI, INILocation, NULL);
    INICloseFile();

    HDD_TAP_PopDir();
  }

  TRACEEXIT;
}
