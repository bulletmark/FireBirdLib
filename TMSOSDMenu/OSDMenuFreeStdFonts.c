#include                "FBLib_TMSOSDMenu.h"

void OSDMenuFreeStdFonts(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuFreeStdFonts");
  #endif

  if(!OSDRgn && !ProgressBarOSDRgn && !InfoBoxOSDRgn && !MessageBoxOSDRgn && !ColorPickerOSDRgn)
  {
    FMUC_FreeFontFile(&OSDMenuFont_10);
    FMUC_FreeFontFile(&OSDMenuFont_12);
    FMUC_FreeFontFile(&OSDMenuFont_14);
    FMUC_FreeFontFile(&OSDMenuFont_16);
    FMUC_FreeFontFile(&OSDMenuFont_18);
    FMUC_FreeFontFile(&OSDMenuFont_20);
    FMUC_FreeFontFile(&OSDMenuFont_20B);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
