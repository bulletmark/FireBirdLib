#include                "FBLib_TMSOSDMenu.h"

void OSDMenuDestroy(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuDestroy");
  #endif

  if(OSDRgn)
  {
    TAP_Osd_Delete(OSDRgn);
    TAP_Osd_Sync();
    OSDRgn = 0;
    if(OSDMenuSelectionBarRgn) TAP_Osd_Delete(OSDMenuSelectionBarRgn);
    OSDMenuSelectionBarRgn = 0;
    OSDMenuLastCursor = LCT_NRCURSORS;
  }
  if((!ProgressBarOSDRgn) && (!InfoBoxOSDRgn) && (!MessageBoxOSDRgn) && (!ColorPickerOSDRgn)) TAP_EnterNormal();
  if(Menu[CurrentMenuLevel].Item) TAP_MemFree(Menu[CurrentMenuLevel].Item);

  OSDMenuFreeStdFonts();

  CallbackProcedure = NULL;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
