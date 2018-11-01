#include                "FBLib_TMSOSDMenu.h"

void OSDMenuFreeStdFonts(void)
{
  TRACEENTER();

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

  TRACEEXIT();
}
