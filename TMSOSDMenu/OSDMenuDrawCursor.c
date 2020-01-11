#include                "FBLib_TMSOSDMenu.h"

void OSDMenuDrawCursor(dword x, dword y, dword w, dword h)
{
  TYPE_GrData              *OSDMenuLightBlueCursorGd, *OSDMenuDarkBlueCursorGd;
  word                      chunks, remainder, cx;
  dword                     Color;

  TRACEENTER();

  if (MenuCursorType == CT_Hide) return;

  if(MenuCursorType == CT_Box)
  {
    Color = RGB(90, 205, 236);
    TAP_Osd_FillBox(OSDRgn, x, y, w, 2, Color);
    TAP_Osd_FillBox(OSDRgn, x + w - 2, y, 2, h, Color);
    TAP_Osd_FillBox(OSDRgn, x, y + h - 2, w, 2, Color);
    TAP_Osd_FillBox(OSDRgn, x, y, 2, h, Color);
  }
  else
  {
    switch (h)
    {
      case 19:
        OSDMenuLightBlueCursorGd = &_Cursor_Blue_Tiny_Gd;
        OSDMenuDarkBlueCursorGd = &_Cursor_Dark_Tiny_Gd;
        break;

      case 23:
        OSDMenuLightBlueCursorGd = &_Cursor_Blue_Small_Gd;
        OSDMenuDarkBlueCursorGd = &_Cursor_Dark_Small_Gd;
        break;

      default:
        OSDMenuLightBlueCursorGd = &_Cursor_Blue_Normal_Gd;
        OSDMenuDarkBlueCursorGd = &_Cursor_Dark_Normal_Gd;
        break;
    }

    //Cursor-St�ck in eine Memory-Region kopieren
    if(OSDMenuLastCursor != LCT_Blue)
    {
      if(OSDMenuSelectionBarRgn) TAP_Osd_Delete(OSDMenuSelectionBarRgn);
      OSDMenuSelectionBarRgn = TAP_Osd_Create(0, 0, OSDMenuLightBlueCursorGd->width, OSDMenuLightBlueCursorGd->height, 0, OSD_Flag_MemRgn);
      TAP_Osd_PutGd(OSDMenuSelectionBarRgn, 0, 0, OSDMenuLightBlueCursorGd, FALSE);
      OSDMenuLastCursor = LCT_Blue;
    }

    chunks = w / OSDMenuLightBlueCursorGd->width;
    remainder = w % OSDMenuLightBlueCursorGd->width;
    cx = x;

    //St�cke
    for (; chunks > 0; chunks--)
    {
      TAP_Osd_Copy(OSDMenuSelectionBarRgn, OSDRgn, 0, 0, OSDMenuLightBlueCursorGd->width, h, cx, y, FALSE);
      cx += OSDMenuLightBlueCursorGd->width;
    }

    //Restliche L�nge
    if (remainder) TAP_Osd_Copy(OSDMenuSelectionBarRgn, OSDRgn, 0, 0, remainder, h, cx, y, FALSE);

    if(MenuCursorType == CT_Dark)
    {
      //Falls via OSDMenuSetCursor ausgew�hlt, dann den dunklen Cursor dr�bermalen
      //Cursor-St�ck in eine Memory-Region kopieren
      if(OSDMenuLastCursor != LCT_BlueDark)
      {
        if(OSDMenuSelectionBarRgn) TAP_Osd_Delete(OSDMenuSelectionBarRgn);
        OSDMenuSelectionBarRgn = TAP_Osd_Create(0, 0, OSDMenuDarkBlueCursorGd->width, OSDMenuDarkBlueCursorGd->height, 0, OSD_Flag_MemRgn);
        TAP_Osd_PutGd(OSDMenuSelectionBarRgn, 0, 0, OSDMenuDarkBlueCursorGd, FALSE);
        OSDMenuLastCursor = LCT_BlueDark;
      }

      chunks = (w - 4) / OSDMenuDarkBlueCursorGd->width;
      remainder = (w - 4) % OSDMenuDarkBlueCursorGd->width;
      cx = x + 2;

      //St�cke
      for (; chunks > 0; chunks--)
      {
        TAP_Osd_Copy(OSDMenuSelectionBarRgn, OSDRgn, 0, 0, OSDMenuDarkBlueCursorGd->width, h, cx, y, FALSE);
        cx += OSDMenuDarkBlueCursorGd->width;
      }

      //Restliche L�nge
      if (remainder) TAP_Osd_Copy(OSDMenuSelectionBarRgn, OSDRgn, 0, 0, remainder, h, cx, y, FALSE);
    }
  }

  TRACEEXIT();
}
