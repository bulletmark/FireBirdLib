#include                "FBLib_TMSOSDMenu.h"

void OSDMenuInfoBoxDestroy(void)
{
  TRACEENTER();

  if(InfoBoxOSDRgn)
  {
    OSDMenuInfoBoxDestroyNoOSDUpdate();
    TAP_Osd_Sync();
  }
  if((!OSDRgn) && (!ProgressBarOSDRgn) && (!MessageBoxOSDRgn) && (!ColorPickerOSDRgn)) TAP_EnterNormal();

  OSDMenuFreeStdFonts();

  TRACEEXIT();
}
