#include                "FBLib_TMSOSDKeyboard.h"

TYPE_GrData *OSDMenuGetIconPointer(tButtonIcon ButtonIcon, TYPE_GrData *UserDefinedButton);

void OSDMenuKeyboard_DrawLegendButton(dword Line, tButtonIcon ButtonIcon, const char *Text)
{
  TRACEENTER();

  TYPE_GrData          *IconGd;
  int                   y;

  IconGd = OSDMenuGetIconPointer(ButtonIcon, NULL);

  if (Line > 0 && Line < 4 && (Text && IconGd))
  {
    switch(Line - 1)
    {
      case 0:  y = 312; break;
      case 1:  y = 336; break;
      case 2:  y = 360; break;
      default: y = 312; break;
    }

    TAP_Osd_PutGd(OSDMenuKeyboard_rgn, OSDMenuKeyboard_ButtonsX[Line - 1], y, IconGd, TRUE);
    FMUC_PutString(OSDMenuKeyboard_rgn, OSDMenuKeyboard_ButtonsX[Line - 1] + IconGd->width + 2, y, 432, Text, COLOR_Grey18, 0, &KeyboardFont_12, FALSE, ALIGN_LEFT);
    OSDMenuKeyboard_ButtonsX[Line - 1] = OSDMenuKeyboard_ButtonsX[Line - 1] + IconGd->width + FMUC_GetStringWidth(Text, &KeyboardFont_12) + 6;
  }

  TRACEEXIT();
}
