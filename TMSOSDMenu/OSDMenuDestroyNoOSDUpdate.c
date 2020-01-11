#include                <stdlib.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuDestroyNoOSDUpdate(void)
{
  TRACEENTER();

  if(OSDRgn)
  {
    TAP_Osd_Delete(OSDRgn);
    OSDRgn = 0;
    if(OSDMenuSelectionBarRgn) TAP_Osd_Delete(OSDMenuSelectionBarRgn);
    OSDMenuSelectionBarRgn = 0;
    OSDMenuLastCursor = LCT_NRCURSORS;
  }
  if(Menu[CurrentMenuLevel].Item)
  {
    TAP_MemFree(Menu[CurrentMenuLevel].Item);
    Menu[CurrentMenuLevel].Item = NULL;
  }

  if (Menu[CurrentMenuLevel].MemoText)
  {
    TAP_MemFree(Menu[CurrentMenuLevel].MemoText);
    Menu[CurrentMenuLevel].MemoText = NULL;
  }

  OSDMenuFreeStdFonts();

  Menu[CurrentMenuLevel].CallbackProcedure = NULL;

  TRACEEXIT();
}
