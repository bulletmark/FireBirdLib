#include                "FBLib_TMSOSDMenu.h"

void OSDMenuProgressBarDestroy(void)
{
  if(ProgressBarOSDRgn)
  {
    TAP_Osd_Delete(ProgressBarOSDRgn);
    TAP_Osd_Delete(ProgressBarFullRgn);
    ProgressBarOSDRgn = 0;
    ProgressBarFullRgn = 0;
  }
  OSDMenuInfoBoxDestroy();
  ProgressBarLastValue =  0xfff;
}
