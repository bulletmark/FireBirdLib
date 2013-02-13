#include                "FBLib_debug.h"

bool CrashCheck_Startup(char *TAPName)
{
  int                   RebootCount;
  INILOCATION           INILocation;

  INILocation = INIOpenFile(CRASHCHECKINI, NULL);
  RebootCount = INIGetInt(TAPName, 0, 0, 100);
  RebootCount++;
  INISetInt(TAPName, RebootCount);
  if(INILocation == INILOCATION_NewFile) INILocation = INILOCATION_AtSettings;
  INISaveFile(CRASHCHECKINI, INILocation, NULL);
  INICloseFile();

  return (RebootCount < 3);
}
