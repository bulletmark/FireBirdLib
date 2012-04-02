#include                "FBLib_TMSOSDMenu.h"

void OSDMenuDestroyNoOSDUpdate(void)
{
  if(OSDRgn)
  {
    TAP_Osd_Delete(OSDRgn);
    OSDRgn = 0;
  }
  if(Menu[CurrentMenuLevel].Item) TAP_MemFree(Menu[CurrentMenuLevel].Item);

  CallbackProcedure = NULL;
}
