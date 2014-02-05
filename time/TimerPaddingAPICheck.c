#include                "../libFireBird.h"

bool TimerPaddingAPICheck(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TimerPaddingAPICheck");
  #endif

  static bool           AlreadyChecked = FALSE;
  static bool           SysVarRecPaddingSupported = FALSE;
  int                   CurrentRecPaddingFore, TempRecPaddingFore;

  //Find out if the firmware already supports the SYSVAR_RecPaddingFore and SYSVAR_RecPaddingRear variables
  if(!AlreadyChecked)
  {
    CurrentRecPaddingFore = TAP_GetSystemVar(SYSVAR_RecPaddingFore);
    TAP_SetSystemVar(SYSVAR_RecPaddingFore, CurrentRecPaddingFore + 1);
    TempRecPaddingFore = TAP_GetSystemVar(SYSVAR_RecPaddingFore);

    if(TempRecPaddingFore == (CurrentRecPaddingFore + 1)) SysVarRecPaddingSupported = TRUE;
    TAP_SetSystemVar(SYSVAR_RecPaddingFore, CurrentRecPaddingFore);

    TAP_PrintNet("TimerPaddingAPICheck: %d %d %s\n", CurrentRecPaddingFore, TempRecPaddingFore, SysVarRecPaddingSupported ? " true" : "false");

    AlreadyChecked = TRUE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return SysVarRecPaddingSupported;
}
