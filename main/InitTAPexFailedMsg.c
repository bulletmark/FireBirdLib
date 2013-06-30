#include                <stdio.h>
#include                "../libFireBird.h"

void InitTAPexFailedMsg(char *ProgramName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("InitTAPexFailedMsg");
  #endif

  char                  s[28];

  TAP_SPrint(s, "%d %4.4x", GetSysID(), ApplID);
  ShowMessageWin(ProgramName ? ProgramName : "", "FBLib failed to init", s, 500);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
