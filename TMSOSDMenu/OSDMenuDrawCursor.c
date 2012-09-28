#include                "FBLib_TMSOSDMenu.h"

#include                "graphic/SelectionBar_Blue_100x34.gd"
#include                "graphic/SelectionBar_Blue_100x34Dark.gd"

void OSDMenuDrawCursor(dword x, dword y, dword w)
{
  TYPE_GrData              *OSDMenuLightBlueCursorGd, *OSDMenuDarkBlueCursorGd;
  int                       pb=0, cx, h, hundret=0, hundretModulo=0;
  dword                     Color;

  OSDMenuLightBlueCursorGd = &_SelectionBar_Blue_100x34_Gd;
  OSDMenuDarkBlueCursorGd = &_SelectionBar_Blue_100x34Dark_Gd;
  h = 34;

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
    //100er-Bar in eine Memory-Region kopieren
    if(OSDMenuLightBlueCursorGd)
    {
      if(OSDMenuLastCursor != LCT_Blue)
      {
        if(OSDMenuSelectionBarRgn) TAP_Osd_Delete(OSDMenuSelectionBarRgn);
        OSDMenuSelectionBarRgn = TAP_Osd_Create(0, 0, OSDMenuLightBlueCursorGd->width, OSDMenuLightBlueCursorGd->height, 0, OSD_Flag_MemRgn);
        TAP_Osd_PutGd(OSDMenuSelectionBarRgn, 0, 0, OSDMenuLightBlueCursorGd, FALSE);
        OSDMenuLastCursor = LCT_Blue;
      }

      hundret = w/100;
      hundretModulo = w%100;
      cx = x;

      //Hunderter
      if(hundret > 0)
      {
        for (pb=0;pb<hundret;pb++)
        {
          TAP_Osd_Copy(OSDMenuSelectionBarRgn, OSDRgn, 0, 0, 100, h, cx, y, FALSE);
          cx += 100;
        }
      }

      //Restliche Länge
      if(hundretModulo > 0) TAP_Osd_Copy(OSDMenuSelectionBarRgn, OSDRgn, 0, 0, hundretModulo, h, cx, y, FALSE);
    }

    if(MenuCursorType == CT_Dark && OSDMenuDarkBlueCursorGd)
    {
      //Falls via OSDMenuSetCursor ausgewählt, dann den dunklen Cursor drübermalen
      //100er-Bar in eine Memory-Region kopieren
      if(OSDMenuLastCursor != LCT_BlueDark)
      {
        if(OSDMenuSelectionBarRgn) TAP_Osd_Delete(OSDMenuSelectionBarRgn);
        OSDMenuSelectionBarRgn = TAP_Osd_Create(0, 0, OSDMenuDarkBlueCursorGd->width, OSDMenuDarkBlueCursorGd->height, 0, OSD_Flag_MemRgn);
        TAP_Osd_PutGd(OSDMenuSelectionBarRgn, 0, 0, OSDMenuDarkBlueCursorGd, FALSE);
        OSDMenuLastCursor = LCT_BlueDark;
      }

      hundret = (w-4)/100;
      hundretModulo = (w-4)%100;
      cx = x+2;

      //Hunderter
      if(hundret > 0)
      {
        for (pb=0;pb<hundret;pb++)
        {
          TAP_Osd_Copy(OSDMenuSelectionBarRgn, OSDRgn, 0, 0, 100, h, cx, y, FALSE);
          cx += 100;
        }
      }

      //Restliche Länge
      if(hundretModulo > 0) TAP_Osd_Copy(OSDMenuSelectionBarRgn, OSDRgn, 0, 0, hundretModulo, h, cx, y, FALSE);
    }
  }
}
