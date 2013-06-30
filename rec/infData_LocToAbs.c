#include <tap.h>
#include "FBLib_rec.h"

char *infData_LocToAbs(char *LocalInfName)
{
  char                  CurrentDir[512];
  static char           AbsPath[512];

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_LocToAbs");
  #endif

  HDD_TAP_GetCurrentDir(CurrentDir);
    TAP_SPrint(AbsPath, "%s%s/%s", TAPFSROOT, CurrentDir, LocalInfName);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return AbsPath;
}
