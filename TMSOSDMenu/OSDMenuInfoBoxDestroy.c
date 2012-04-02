#include                "FBLib_TMSOSDMenu.h"

void OSDMenuInfoBoxDestroy(void)
{
  if(InfoBoxOSDRgn)
  {
    OSDMenuInfoBoxDestroyNoOSDUpdate();
    TAP_Osd_Sync();
    if((!OSDRgn) && (!ProgressBarOSDRgn) && (!MessageBoxOSDRgn) && (!ColorPickerOSDRgn)) TAP_EnterNormal();
  }
}
