#include                "FBLib_TMSOSDMenu.h"

void OSDDrawBackground(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDDrawBackground");
  #endif

  TAP_Osd_Draw3dBoxFill(OSDRgn,  0,  0, 720, 576, RGB(16, 16, 16), RGB(16, 16, 16), RGB(16, 16, 16));
  TAP_Osd_FillBox(OSDRgn, 50, 479, 614, 2, RGB(128, 128, 128));

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
