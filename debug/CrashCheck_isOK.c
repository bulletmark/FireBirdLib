#include                "FBLib_debug.h"

bool CrashCheck_isOK(char *TAPName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("CrashCheck_isOK");
  #endif

  int                   RebootCount = 0;
  INILOCATION           INILocation;

  if(TAPName)
  {
    INILocation = INIOpenFile(CRASHCHECKINI, NULL);
    RebootCount = INIGetInt(TAPName, 0, 0, 100);
    INICloseFile();
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (RebootCount == 0);
}
