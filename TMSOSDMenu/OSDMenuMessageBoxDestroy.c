#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxDestroy(void)
{
  if(MessageBoxOSDRgn)
  {
    OSDMenuMessageBoxDestroyNoOSDUpdate();
    TAP_Osd_Sync();
  }
  if((!OSDRgn) && (!InfoBoxOSDRgn) && (!ProgressBarOSDRgn) && (!ColorPickerOSDRgn)) TAP_EnterNormal();
}
