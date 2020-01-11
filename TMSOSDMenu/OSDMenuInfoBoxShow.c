#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

dword WaitSpinnerPosY;

void OSDMenuInfoBoxShow(const char *Title, const char *Text, dword Timeout)
{
  TRACEENTER();

  dword                 x, y, dy, i;
  char                 *pText;
  char                 *EndOfText;
  dword                 Lines;
  char                  s[256];
  tOSDMapInfo          *OSDMapInfo;

  if(MessageBoxOSDRgn)OSDMenuMessageBoxDestroy();

  OSDMenuLoadStdFonts();

  if(!InfoBoxOSDRgn)
  {
    x = (720 - _InfoBox_Gd.width) >> 1;
    y = (576 - _InfoBox_Gd.height) >> 1;
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
        InfoBoxSaveArea = TAP_Osd_SaveBox(OSDRgn, InfoBoxSaveAreaX, InfoBoxSaveAreaY, _InfoBox_Gd.width, _InfoBox_Gd.height);
    }

    InfoBoxOSDRgn = TAP_Osd_Create(x, y, _InfoBox_Gd.width, _InfoBox_Gd.height, 0, 0);
    TAP_ExitNormal();
  }
  TAP_Osd_PutGd(InfoBoxOSDRgn, 0, 0, &_InfoBox_Gd, FALSE);

  OSDMenuPutS(InfoBoxOSDRgn, 0, 10, 380, Title, RGB(232,146,17), COLOR_None, 14, FALSE, ALIGN_CENTER);

  //Count the number of lines
  strncpy(s, Text, 255);
  s[255] = '\0';
  pText = s;
  EndOfText = s + strlen(s);
  Lines = 0;
  while(pText < EndOfText)
  {
    Lines++;
    pText = strpbrk(pText, "\x0d\x0a");
    if(!pText) break;
    *pText = '\0';
    pText++;
    if (Lines == 7) break;
  }

  dy = 20;
  y = 70 - 10 * (Lines - 1);
  pText = s;
  for(i = 0; i < Lines; i++)
  {
    OSDMenuPutS(InfoBoxOSDRgn, 0, y - 7 + 36, 380, pText, RGB(192,192,192), COLOR_None, 14, FALSE, ALIGN_CENTER);
    y += dy;
    pText += (strlen(pText) + 1);
  }

  WaitSpinnerPosY = (Lines == 6 ? 164 : 158) + ((24 - WaitSpinnerItemHeight) >> 1);

  if(Timeout)
    InfoBoxTimeOut = TAP_GetTick() + Timeout;
  else
  {
    if (InfoBoxExitButton) TAP_Osd_PutGd(InfoBoxOSDRgn, _InfoBox_Gd.width - _Button_exit_Gd.width - 8, Lines == 6 ? 167 : 163, &_Button_exit_Gd, TRUE);

    InfoBoxTimeOut = 0xffffffff;
  }

  TAP_Osd_Sync();

  TRACEEXIT();
}
