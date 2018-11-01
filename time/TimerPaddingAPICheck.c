#include                "libFireBird.h"

bool TimerPaddingAPICheck(void)
{
  TRACEENTER();

  static bool           AlreadyChecked = FALSE;
  static bool           SysVarRecPaddingSupported = FALSE;
  int                   CurrentRecPaddingFore, TempRecPaddingFore, CurrentRecPaddingRear;

  //Find out if the firmware already supports the SYSVAR_RecPaddingFore and SYSVAR_RecPaddingRear variables
  if(!AlreadyChecked)
  {
    CurrentRecPaddingFore = TAP_GetSystemVar(SYSVAR_RecPaddingFore);
    TAP_SetSystemVar(SYSVAR_RecPaddingFore, CurrentRecPaddingFore + 1);
    TempRecPaddingFore = TAP_GetSystemVar(SYSVAR_RecPaddingFore);

    if(TempRecPaddingFore == (CurrentRecPaddingFore + 1)) SysVarRecPaddingSupported = TRUE;
    TAP_SetSystemVar(SYSVAR_RecPaddingFore, CurrentRecPaddingFore);
    CurrentRecPaddingRear = TAP_GetSystemVar(SYSVAR_RecPaddingRear);

    LogEntryFBLibPrintf(TRUE, "TimerPaddingAPICheck: %d %d %d %s", CurrentRecPaddingFore, TempRecPaddingFore, CurrentRecPaddingRear, SysVarRecPaddingSupported ? " true" : "false");

    AlreadyChecked = TRUE;
  }

  TRACEEXIT();
  return SysVarRecPaddingSupported;
}
