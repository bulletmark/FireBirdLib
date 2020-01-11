#include                "FBLib_TMSOSDMenu.h"

void OSDDrawButtons(void)
{
  TRACEENTER();

  tMenu                *pMenu;
  dword                 i;

  pMenu = &Menu[CurrentMenuLevel];

  if (pMenu->OSDMenuDisplayMode == OMDM_ListBox) TAP_Osd_FillBox(OSDRgn, pMenu->XPos - LISTBOX_GAP_FRAME_TO_X, 481, pMenu->Width + LISTBOX_ADDITIONAL_WIDTH - 2 * LISTBOX_FRAME_THICKNESS, 54, RGB(16, 16, 16));
  else TAP_Osd_FillBox(OSDRgn, 0, 481, 720, 95, RGB(16, 16, 16));

  for(i = 0; i < pMenu->NrButtons; i++)
  {
    TAP_Osd_PutGd(OSDRgn, pMenu->Buttons[i].X , pMenu->Buttons[i].Y, pMenu->Buttons[i].pButtonGd, TRUE);
    FMUC_PutStringAA(OSDRgn, pMenu->Buttons[i].X + pMenu->Buttons[i].pButtonGd->width + 2, pMenu->Buttons[i].Y + 3 + FONTYOFFSET, pMenu->XPos + pMenu->Width - 2, pMenu->Buttons[i].Text, pMenu->Buttons[i].Color, COLOR_None, pMenu->FontButtons, FALSE, ALIGN_LEFT, 1);
  }

  if (pMenu->CallbackProcedure) pMenu->CallbackProcedure(OSDCB_Buttons, OSDRgn);

  TRACEEXIT();
}
