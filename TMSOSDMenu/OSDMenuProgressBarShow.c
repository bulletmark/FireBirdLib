#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

#define PROGRESSBARX    234
#define PROGRESSBARY    330

void OSDMenuProgressBarShow(char *Title, char *Text, dword Value, dword MaxValue, TYPE_GrData *DifferentProgressBar)
{
  TRACEENTER();

  if(Value != ProgressBarLastValue)
  {
    OSDMenuInfoBoxShow(Title, Text, 0x7fffffff);
    if(!ProgressBarOSDRgn)
    {
      ProgressBarOSDRgn = TAP_Osd_Create(PROGRESSBARX, PROGRESSBARY, _InputBox_Gd.width, _InputBox_Gd.height, 0, 0);
      ProgressBarFullRgn = TAP_Osd_Create(0, 0, _Progressbar_Gd.width, _Progressbar_Gd.height, 0, OSD_Flag_MemRgn);
    }
    TAP_Osd_PutGd(ProgressBarFullRgn, 0, 0, (DifferentProgressBar ? DifferentProgressBar : &_Progressbar_Gd), FALSE);
    TAP_Osd_PutGd(ProgressBarOSDRgn, 0, 0, &_InputBox_Gd, FALSE);
    TAP_Osd_Copy(ProgressBarFullRgn, ProgressBarOSDRgn, 0, 0, _InputBox_Gd.width * Value / MaxValue, _InputBox_Gd.height, 0, 0, FALSE);
    TAP_Osd_Sync();
    ProgressBarLastValue = Value;
  }

  TRACEEXIT();
}
