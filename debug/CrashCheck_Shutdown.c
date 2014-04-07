#include                "FBLib_debug.h"

void CrashCheck_Shutdown(char *TAPName)
{
  TRACEENTER();

  INILOCATION           INILocation;

  if(TAPName)
  {
    INILocation = INIOpenFile(CRASHCHECKINI, NULL);
    INISetInt(TAPName, 0);
    if(INILocation == INILOCATION_NewFile) INILocation = INILOCATION_AtSettings;
    INISaveFile(CRASHCHECKINI, INILocation, NULL);
    INICloseFile();
  }

  TRACEEXIT();
}
