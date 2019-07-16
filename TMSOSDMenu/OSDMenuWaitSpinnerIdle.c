#include                "FBLib_TMSOSDMenu.h"

void OSDMenuWaitSpinnerIdle(void)
{
  TRACEENTER();

  if(TAP_GetTick() > WaitSpinnerTimeout)
  {
    int i, trail = 0;

    for (i = WaitSpinnerIndex; i >= 0; i--)
    {
      dword x, r, g, b;

      if (i < WaitSpinnerItems) x = i * WaitSpinnerItemWidth * 2;
      else x = (i - WaitSpinnerItems) * WaitSpinnerItemWidth * 2;

      r = R8888(WaitSpinnerItemColorTrail) + trail * (R8888(WaitSpinnerItemColorBlank) - R8888(WaitSpinnerItemColorTrail)) / WaitSpinnerItemsTrail;
      g = G8888(WaitSpinnerItemColorTrail) + trail * (G8888(WaitSpinnerItemColorBlank) - G8888(WaitSpinnerItemColorTrail)) / WaitSpinnerItemsTrail;
      b = B8888(WaitSpinnerItemColorTrail) + trail * (B8888(WaitSpinnerItemColorBlank) - B8888(WaitSpinnerItemColorTrail)) / WaitSpinnerItemsTrail;

      OSDMenuWaitSpinnerDrawItem(WaitSpinnerRgn, x, RGB(r, g, b));

      if (++trail == WaitSpinnerItemsTrail && i > 0)
      {
        OSDMenuWaitSpinnerDrawItem(WaitSpinnerRgn, (i - 1) * WaitSpinnerItemWidth * 2, WaitSpinnerItemColorBlank);
        break;
      }
    }

    if (WaitSpinnerIndex == WaitSpinnerItems + WaitSpinnerItemsTrail - 1) WaitSpinnerIndex = WaitSpinnerItemsTrail;
    else WaitSpinnerIndex++;

    TAP_Osd_Copy(WaitSpinnerRgn, InfoBoxOSDRgn, 0, 0, WaitSpinnerWidth, WaitSpinnerItemHeight, (_InfoBox_Gd.width - WaitSpinnerWidth) >> 1, WaitSpinnerPosY, FALSE);
    TAP_Osd_Sync();

    WaitSpinnerTimeout = TAP_GetTick() + WaitSpinnerSpeed;
  }

  TRACEEXIT();
}
