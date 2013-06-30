#include                "FBLib_debug.h"

void CrashCheck_Shutdown(char *TAPName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("CrashCheck_Shutdown");
  #endif

  INILOCATION           INILocation;

  if(TAPName)
  {
    INILocation = INIOpenFile(CRASHCHECKINI, NULL);
    INISetInt(TAPName, 0);
    if(INILocation == INILOCATION_NewFile) INILocation = INILOCATION_AtSettings;
    INISaveFile(CRASHCHECKINI, INILocation, NULL);
    INICloseFile();
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
