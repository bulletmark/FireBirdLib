#include "FBLib_TMSOSDMenu.h"

void OSDMenuWaitSpinnerDrawItem (word rgn, dword x, dword rgb)
{
  word i, y = 0;

  TRACEENTER();

  for (i = 0; i < WaitSpinnerItemHeight; i++)
  {
    dword off = 0;

    if (i == 0 || i == WaitSpinnerItemHeight - 1) off = 1;

    TAP_Osd_FillBox(rgn, x + off, y++, WaitSpinnerItemWidth - (off << 1), 1, OSDMenuWaitSpinnerShadeColor(rgb, i, WaitSpinnerItemHeight));
  }

  TRACEEXIT();
}
