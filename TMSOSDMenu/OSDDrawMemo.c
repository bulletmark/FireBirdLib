#include                "FBLib_TMSOSDMenu.h"

void OSDDrawMemo(void)
{
  TRACEENTER();

  int                   dLines, i;
  dword                 Y;
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  dLines = (pMenu->NrLines == 18 ? 20 : 24);

  //The background
  TAP_Osd_Draw3dBoxFill(OSDRgn, 60, 96, 600, 368, RGB(30, 30, 30), RGB(30, 30, 30), RGB(30, 30, 30));

  for(i = 0; i < pMenu->NrLines; i++)
  {
    Y = 99 + (i * dLines);

    //The text of the left column
    if((i + pMenu->CurrentTopIndex) < pMenu->NrItems)
      FMUC_PutStringAA(OSDRgn, 76, Y + 5 + FONTYOFFSET, 645, pMenu->Item[i + pMenu->CurrentTopIndex].Name, RGB(255, 255, 255), COLOR_None, pMenu->FontMemo, TRUE, ALIGN_LEFT, 1);
  }

  if(CallbackProcedure) CallbackProcedure(OSDCB_List, OSDRgn);

  TRACEEXIT();
}
