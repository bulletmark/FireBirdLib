#include                "FBLib_TMSOSDMenu.h"

void OSDMenuWaitSpinnerInit(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuWaitSpinnerInit");
  #endif

  if(InfoBoxOSDRgn && WaitSpinnerRgn == 0)
  {
    WaitSpinnerRgn = TAP_Osd_Create(0, 0, _WaitSpinner_All_Gd.width, _WaitSpinner_All_Gd.height, 0, OSD_Flag_MemRgn);
    if(WaitSpinnerRgn)
    {
      TAP_Osd_PutGd(WaitSpinnerRgn, 0, 0, &_WaitSpinner_All_Gd, FALSE);
      TAP_Osd_Copy(WaitSpinnerRgn, InfoBoxOSDRgn, 0, 0, 50, 50, 15, 130, FALSE);
      WaitSpinnerIndex = 0;
      WaitSpinnerTimeout = TAP_GetTick() + 10;
      TAP_Osd_Sync();
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
