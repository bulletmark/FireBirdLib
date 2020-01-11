#include                "FBLib_TMSOSDMenu.h"

void OSDDrawTitle(void)
{
  TRACEENTER();

  dword                 tw;
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if (pMenu->OSDMenuDisplayMode == OMDM_ListBox)
  {
    TAP_Osd_FillBox(OSDRgn, pMenu->XPos - LISTBOX_GAP_FRAME_TO_X, 44 + LISTBOX_FRAME_THICKNESS, pMenu->Width + LISTBOX_ADDITIONAL_WIDTH - 2 * LISTBOX_FRAME_THICKNESS, 50, RGB(16, 16, 16));
    FMUC_PutStringAA(OSDRgn, pMenu->XPos, 61 + FONTYOFFSET, pMenu->XPos + pMenu->Width - 1, Menu[CurrentMenuLevel].TitleLeft, RGB(230,230,250), COLOR_None, pMenu->FontRightTitle, FALSE, ALIGN_CENTER, 1);
  }
  else
  {
    TAP_Osd_FillBox(OSDRgn, 0, 0, 720, 96, RGB(16, 16, 16));
    FMUC_PutStringAA(OSDRgn, 50, 39 + FONTYOFFSET, 658, Menu[CurrentMenuLevel].TitleLeft, RGB(230,230,250), COLOR_None, pMenu->FontLeftTitle, FALSE, ALIGN_LEFT, 1);
    tw = FMUC_GetStringWidth(Menu[CurrentMenuLevel].TitleLeft, pMenu->FontLeftTitle);

    FMUC_PutStringAA(OSDRgn, 50 + tw + 5, 49 + FONTYOFFSET, 658, Menu[CurrentMenuLevel].TitleRight, RGB(102,102,102), COLOR_None, pMenu->FontRightTitle, TRUE, ALIGN_RIGHT, 1);
  }

  if (pMenu->CallbackProcedure) pMenu->CallbackProcedure(OSDCB_Title, OSDRgn);

  TRACEEXIT();
}
