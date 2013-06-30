#include                "FBLib_TMSOSDMenu.h"

void OSDMenuInfoBoxDestroy(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuInfoBoxDestroy");
  #endif

  if(InfoBoxOSDRgn)
  {
    OSDMenuInfoBoxDestroyNoOSDUpdate();
    TAP_Osd_Sync();
  }
  if((!OSDRgn) && (!ProgressBarOSDRgn) && (!MessageBoxOSDRgn) && (!ColorPickerOSDRgn)) TAP_EnterNormal();

  OSDMenuFreeStdFonts();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
