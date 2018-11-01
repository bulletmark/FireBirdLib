#include                "FBLib_debug.h"

void CrashCheck_Startup(char *TAPName, tCrashCheckStatus *CCStatus)
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
    RebootCount++;
    INISetInt(TAPName, RebootCount);
    if(INILocation == INILOCATION_NewFile) INILocation = INILOCATION_AtSettings;
    INISaveFile(CRASHCHECKINI, INILocation, NULL);
    INICloseFile();

    HDD_TAP_PopDir();
  }

  if(CCStatus)
  {
    if(RebootCount < 2) *CCStatus = CCS_Ok;
    else if(RebootCount < 4) *CCStatus = CCS_RebootDetected;
    else *CCStatus = CCS_ExcessiveRebootsDetected;
  }

  TRACEEXIT();
}
