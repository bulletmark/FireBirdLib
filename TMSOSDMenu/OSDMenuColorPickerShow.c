#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuColorPickerShow(char *Title, dword Color)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuColorPickerShow");
  #endif

  dword                 x, y;
  tOSDMapInfo          *OSDMapInfo;

  ColorPickerDefaultColor = Color;
  ColorPickerColor = Color;
  CurrentColorSelected = CCS_Red;
  ColorPickerLastCursorRed = -1;
  ColorPickerLastCursorGreen = -1;
  ColorPickerLastCursorBlue = -1;

  if(!ColorPickerOSDRgn)
  {
    x = (720 - _ColorPicker_Gd.width) >> 1;
    y = (576 - _ColorPicker_Gd.height) >> 1;
    if(OSDRgn || MyOSDRgn)
    {
      InfoBoxSaveAreaX = x;
      InfoBoxSaveAreaY = y;
      if(MyOSDRgn)
      {
        OSDMapInfo = (tOSDMapInfo*) FIS_vOsdMap();
        if(OSDMapInfo)
          InfoBoxSaveArea = TAP_Osd_SaveBox(MyOSDRgn, InfoBoxSaveAreaX - OSDMapInfo[MyOSDRgn].x, InfoBoxSaveAreaY - OSDMapInfo[MyOSDRgn].y, _InfoBox_Gd.width, _InfoBox_Gd.height);
      }
      else
        InfoBoxSaveArea = TAP_Osd_SaveBox(OSDRgn, InfoBoxSaveAreaX, InfoBoxSaveAreaY, _ColorPicker_Gd.width, _ColorPicker_Gd.height);
    }

    ColorPickerOSDRgn = TAP_Osd_Create(x, y, _ColorPicker_Gd.width, _ColorPicker_Gd.height, 0, 0);
    TAP_ExitNormal();
  }
  TAP_Osd_PutGd(ColorPickerOSDRgn, 0, 0, &_ColorPicker_Gd, FALSE);

  OSDMenuPutS(ColorPickerOSDRgn, 0, 10, 380, Title, RGB(232,146,17), COLOR_None, 14, FALSE, ALIGN_CENTER);

  x = 10;
  TAP_Osd_PutGd(ColorPickerOSDRgn, x , 115, &_Button_red_Gd, TRUE);
  x += (_Button_red_Gd.width + 2);
  TAP_Osd_PutGd(ColorPickerOSDRgn, x , 115, &_Button_green_Gd, TRUE);
  x += (_Button_green_Gd.width + 2);
  TAP_Osd_PutGd(ColorPickerOSDRgn, x , 115, &_Button_blue_Gd, TRUE);
  x += (_Button_blue_Gd.width + 5);
  TAP_Osd_PutGd(ColorPickerOSDRgn, x , 115, &_Button_ok_Gd, TRUE);
  x += (_Button_ok_Gd.width + 5);
  TAP_Osd_PutGd(ColorPickerOSDRgn, x , 115, &_Button_exit_Gd, TRUE);

  OSDMenuColorPickerDrawCursor(CCS_Red, TRUE);
  OSDMenuColorPickerDrawCursor(CCS_Green, FALSE);
  OSDMenuColorPickerDrawCursor(CCS_Blue, FALSE);

  TAP_Osd_Sync();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
