#include                "FBLib_TMSOSDMenu.h"

void OSDMenuWaitSpinnerIdle(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuWaitSpinnerIdle");
  #endif

  if(TAP_GetTick() > WaitSpinnerTimeout)
  {
    WaitSpinnerTimeout = TAP_GetTick() + 10;
    WaitSpinnerIndex = (WaitSpinnerIndex + 1) % 20;
    TAP_Osd_Copy(WaitSpinnerRgn, InfoBoxOSDRgn, 50 * WaitSpinnerIndex, 0, 50, 50, 15, 130, FALSE);
    TAP_Osd_Sync();
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
