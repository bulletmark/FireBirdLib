#include                "FBLib_TMSOSDMenu.h"

void OSDDrawScrollBar(void)
{
  TRACEENTER();

  tMenu                *pMenu;
  word                  extralines = 0, cutY;
  int                   n, l, Y;

  pMenu = &Menu[CurrentMenuLevel];

  if (pMenu->OSDMenuDisplayMode == OMDM_Standard || pMenu->OSDMenuDisplayMode == OMDM_ListBox)
  {
    switch (pMenu->NrLines)
    {
      case 18:
        extralines = 8;
        break;

      case 15:
        extralines = 5;
        break;
    }
  }

  cutY = 96 + _ScrollBarVisible_Gd.height - 16;   // same for ScrollBarInvisible

  if(pMenu->NrItems < pMenu->NrLines + 1)
  {
    TAP_Osd_PutGd(OSDRgn, pMenu->XPos + pMenu->Width + 1, 96, &_ScrollBarInvisible_Gd, FALSE);

    if (extralines) TAP_Osd_Copy(OSDRgn, OSDRgn, pMenu->XPos + pMenu->Width + 1, cutY, _ScrollBarInvisible_Gd.width, 16, pMenu->XPos + pMenu->Width + 1, cutY + extralines, FALSE);
  }
  else
  {
    TAP_Osd_PutGd(OSDRgn, pMenu->XPos + pMenu->Width + 1, 96, &_ScrollBarVisible_Gd, FALSE);

    if (extralines) TAP_Osd_Copy(OSDRgn, OSDRgn, pMenu->XPos + pMenu->Width + 1, cutY, _ScrollBarVisible_Gd.width, 16, pMenu->XPos + pMenu->Width + 1, cutY + extralines, FALSE);

    n = (pMenu->OSDMenuDisplayMode == OMDM_Text ? pMenu->NrLines : 1);
    l = _ScrollBarVisible_Gd.height + extralines - 2 * 12 - _ScrollBarKnob_Gd.height;
    Y = 96 + 12 + (pMenu->CurrentSelection * l) / (pMenu->NrItems - n);

    TAP_Osd_PutGd(OSDRgn, pMenu->XPos + pMenu->Width + 2, Y, &_ScrollBarKnob_Gd, FALSE);
  }

  TRACEEXIT();
}
