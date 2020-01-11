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
  TAP_Osd_Draw3dBoxFill(OSDRgn, pMenu->XPos, 96, pMenu->Width, 368, RGB(30, 30, 30), RGB(30, 30, 30), RGB(30, 30, 30));

  for(i = 0; i < pMenu->NrLines; i++)
  {
    Y = 99 + (i * dLines);

    //The text of the left column
    if((i + pMenu->CurrentTopIndex) < pMenu->NrItems)
      FMUC_PutStringAA(OSDRgn, pMenu->XPos + 16, Y + 5 + FONTYOFFSET, pMenu->XPos + pMenu->Width - 15, pMenu->Item[i + pMenu->CurrentTopIndex].Name, RGB(255, 255, 255), COLOR_None, pMenu->FontMemo, TRUE, ALIGN_LEFT, 1);
  }

  if (pMenu->CallbackProcedure) pMenu->CallbackProcedure(OSDCB_List, OSDRgn);

  TRACEEXIT();
}
