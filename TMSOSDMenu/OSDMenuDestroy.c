#include                "FBLib_TMSOSDMenu.h"

void OSDMenuDestroy(void)
{
  if(OSDRgn)
  {
    TAP_Osd_Delete(OSDRgn);
    TAP_Osd_Sync();
    OSDRgn = 0;
  }
  if((!ProgressBarOSDRgn) && (!InfoBoxOSDRgn) && (!MessageBoxOSDRgn) && (!ColorPickerOSDRgn)) TAP_EnterNormal();
  if(Menu[CurrentMenuLevel].Item) TAP_MemFree(Menu[CurrentMenuLevel].Item);

  CallbackProcedure = NULL;
}
