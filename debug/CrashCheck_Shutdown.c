#include                "FBLib_debug.h"

void CrashCheck_Shutdown(char *TAPName)
{
  INILOCATION           INILocation;

  INILocation = INIOpenFile(CRASHCHECKINI, NULL);
  INISetInt(TAPName, 0);
  if(INILocation == INILOCATION_NewFile) INILocation = INILOCATION_AtSettings;
  INISaveFile(CRASHCHECKINI, INILocation, NULL);
  INICloseFile();
}
