#include                "FBLib_debug.h"

bool CrashCheck_isOK(char *TAPName)
{
  TRACEENTER();

  int                   RebootCount = 0;
  INILOCATION           INILocation;

  if(TAPName)
  {
    INILocation = INIOpenFile(CRASHCHECKINI, NULL);
    RebootCount = INIGetInt(TAPName, 0, 0, 100);
    INICloseFile();
  }

  TRACEEXIT();
  return (RebootCount == 0);
}
