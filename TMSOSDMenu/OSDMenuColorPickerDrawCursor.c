#include                "FBLib_TMSOSDMenu.h"

void OSDMenuColorPickerDrawCursor(tCurrentColorSelected CursorColor, bool Selected)
{
  TRACEENTER();

  int                  y = 0, CurrentX = 0, NewX = 0, TextY = 0;
  char                 s[24];
  TYPE_GrData          *MB;

  #define CURSORXOFFET   8

  if(ColorPickerOSDRgn)
  {
    switch(CursorColor)
    {
      case CCS_Red:
      {
        y = 58;
        TextY = 46;
        CurrentX = ColorPickerLastCursorRed;
        NewX = ((ColorPickerColor >> 16) & 0xff) + CURSORXOFFET;
        ColorPickerLastCursorRed = NewX;
        break;
      }

      case CCS_Green:
      {
        y = 80;
        TextY =68;
        CurrentX = ColorPickerLastCursorGreen;
        NewX = ((ColorPickerColor >> 8) & 0xff) + CURSORXOFFET;
        ColorPickerLastCursorGreen = NewX;
        break;
      }

      case CCS_Blue:
      {
        y = 102;
        TextY = 90;
        CurrentX = ColorPickerLastCursorBlue;
        NewX = (ColorPickerColor & 0xff) + CURSORXOFFET;
        ColorPickerLastCursorBlue = NewX;
        break;
      }
    }

    if(CurrentX > -1)TAP_Osd_PutGd(ColorPickerOSDRgn, CurrentX , y, &_ColorPicker_CursorNone_Gd, FALSE);
    TAP_Osd_PutGd(ColorPickerOSDRgn, NewX , y, &_ColorPicker_CursorDeselected_Gd, FALSE);

    MB = &_ColorPicker_ValueBackroundSelected_Gd;
    TAP_SPrint(s, "%d", NewX - CURSORXOFFET);
    if(Selected)
    {
      TAP_Osd_PutGd(ColorPickerOSDRgn, 310 - (MB->width >> 1), TextY, MB, FALSE);
      OSDMenuPutS(ColorPickerOSDRgn, 310 - (MB->width >> 1), TextY, 310 + (MB->width >> 1), s, RGB(40,40,40), COLOR_None, 12, FALSE, ALIGN_CENTER);
    }
    else
    {
      TAP_Osd_FillBox(ColorPickerOSDRgn, 280, TextY, 60, 17, RGB(40,40,40));
      OSDMenuPutS(ColorPickerOSDRgn, 310 - (MB->width >> 1), TextY, 310 + (MB->width >> 1), s, RGB(192,192,192), COLOR_None, 12, FALSE, ALIGN_CENTER);
    }

    TAP_Osd_FillBox(ColorPickerOSDRgn, 212, 119, 60, 18, ColorPickerColor | 0xff000000);
    TAP_Osd_DrawRectangle(ColorPickerOSDRgn, 212, 119, 60, 18, 1, RGB(192,192,192));
  }

  TRACEEXIT();
}
