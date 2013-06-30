#include                "FBLib_TMSOSDMenu.h"

void OSDDrawButtons(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDDrawButtons");
  #endif

  tMenu                *pMenu;
  dword                 i;

  pMenu = &Menu[CurrentMenuLevel];

  for(i = 0; i < pMenu->NrButtons; i++)
  {
    TAP_Osd_PutGd(OSDRgn, pMenu->Buttons[i].X , pMenu->Buttons[i].Y, pMenu->Buttons[i].pButtonGd, TRUE);
    FMUC_PutStringAA(OSDRgn, pMenu->Buttons[i].X + pMenu->Buttons[i].pButtonGd->width + 2, pMenu->Buttons[i].Y + 3 + FONTYOFFSET, 670, pMenu->Buttons[i].Text, pMenu->Buttons[i].Color, COLOR_None, pMenu->FontButtons, FALSE, ALIGN_LEFT, 1);
  }

  if(CallbackProcedure) CallbackProcedure(OSDCB_Buttons, OSDRgn);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
