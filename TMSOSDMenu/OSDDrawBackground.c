#include                "FBLib_TMSOSDMenu.h"

void OSDDrawBackground(void)
{
  tMenu                *pMenu;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  if (pMenu->OSDMenuDisplayMode == OMDM_ListBox)
  {
    TAP_Osd_Draw3dBoxFill(OSDRgn, pMenu->XPos - LISTBOX_OFFSET_TO_X, 44, pMenu->Width + LISTBOX_ADDITIONAL_WIDTH, 493, RGB(16, 16, 16), RGB(16, 16, 16), RGB(16, 16, 16));
    TAP_Osd_DrawRectangle(OSDRgn, pMenu->XPos - LISTBOX_OFFSET_TO_X, 44, pMenu->Width + LISTBOX_ADDITIONAL_WIDTH, 493, LISTBOX_FRAME_THICKNESS, RGB(128, 128, 128));
  }
  else
  {
    TAP_Osd_Draw3dBoxFill(OSDRgn,  0,  0, 720, 576, RGB(16, 16, 16), RGB(16, 16, 16), RGB(16, 16, 16));
    TAP_Osd_FillBox(OSDRgn, 50, 479, 614, 2, RGB(128, 128, 128));
  }

  TRACEEXIT();
}
