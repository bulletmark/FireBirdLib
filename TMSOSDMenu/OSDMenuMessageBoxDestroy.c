#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxDestroy(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuMessageBoxDestroy");
  #endif

  if(MessageBoxOSDRgn)
  {
    OSDMenuMessageBoxDestroyNoOSDUpdate();
    TAP_Osd_Sync();
  }
  if((!OSDRgn) && (!InfoBoxOSDRgn) && (!ProgressBarOSDRgn) && (!ColorPickerOSDRgn)) TAP_EnterNormal();

  OSDMenuFreeStdFonts();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
