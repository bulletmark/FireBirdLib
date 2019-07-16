#include                "FBLib_TMSOSDMenu.h"

void OSDDrawButtons(void)
{
  TRACEENTER();

  tMenu                *pMenu;
  dword                 i;

  TAP_Osd_FillBox(OSDRgn, 0, 481, 720, 95, RGB(16, 16, 16));

  pMenu = &Menu[CurrentMenuLevel];

  for(i = 0; i < pMenu->NrButtons; i++)
  {
    TAP_Osd_PutGd(OSDRgn, pMenu->Buttons[i].X , pMenu->Buttons[i].Y, pMenu->Buttons[i].pButtonGd, TRUE);
    FMUC_PutStringAA(OSDRgn, pMenu->Buttons[i].X + pMenu->Buttons[i].pButtonGd->width + 2, pMenu->Buttons[i].Y + 3 + FONTYOFFSET, 658, pMenu->Buttons[i].Text, pMenu->Buttons[i].Color, COLOR_None, pMenu->FontButtons, FALSE, ALIGN_LEFT, 1);
  }

  if(CallbackProcedure) CallbackProcedure(OSDCB_Buttons, OSDRgn);

  TRACEEXIT();
}
