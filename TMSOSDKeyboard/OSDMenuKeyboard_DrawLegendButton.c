#include                "FBLib_TMSOSDKeyboard.h"

TYPE_GrData *OSDMenuGetIconPointer(tButtonIcon ButtonIcon, TYPE_GrData *UserDefinedButton);

void OSDMenuKeyboard_DrawLegendButton(dword Line, tButtonIcon ButtonIcon, char *Text)
{
  TYPE_GrData          *IconGd;
  extern tFontData      Calibri_12_FontData;
  int                   y;

  if(Line > 0 && Line < 4)
  {
    switch(Line - 1)
    {
      case 0:  y = 312; break;
      case 1:  y = 336; break;
      case 2:  y = 360; break;
      default: y = 312; break;
    }

    IconGd = OSDMenuGetIconPointer(ButtonIcon, NULL);
    TAP_Osd_PutGd(OSDMenuKeyboard_rgn, OSDMenuKeyboard_ButtonsX[Line - 1], y, IconGd, TRUE);
    FM_PutString(OSDMenuKeyboard_rgn, OSDMenuKeyboard_ButtonsX[Line - 1] + IconGd->width + 2, y, 430, Text, COLOR_Grey18, 0, &Calibri_12_FontData, FALSE, ALIGN_LEFT);
    OSDMenuKeyboard_ButtonsX[Line - 1] = OSDMenuKeyboard_ButtonsX[Line - 1] + IconGd->width + FM_GetStringWidth(Text, &Calibri_12_FontData) + 6;
  }
}
