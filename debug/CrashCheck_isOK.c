#include                "FBLib_debug.h"

bool CrashCheck_isOK(char *TAPName)
{
  TRACEENTER();

  int                   RebootCount = 0;
  INILOCATION           INILocation;

  if(TAPName)
  {
    HDD_TAP_PushDir();
    HDD_ChangeDir("/ProgramFiles/Settings");

    INILocation = INIOpenFile(CRASHCHECKINI, NULL);
    RebootCount = INIGetInt(TAPName, 0, 0, 100);
    INICloseFile();

    HDD_TAP_PopDir();
  }

  TRACEEXIT();
  return (RebootCount == 0);
}
