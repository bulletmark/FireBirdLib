#include                "FBLib_TMSOSDMenu.h"

void OSDDrawMemo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDDrawMemo");
  #endif

  int                   i;
  dword                 Y;
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  //The background
  TAP_Osd_Draw3dBoxFill(OSDRgn, 60, 96, 600, 367, RGB(30, 30, 30), RGB(30, 30, 30), RGB(30, 30, 30));

  for(i = 0; i < 15; i++)
  {
    Y = 99 + (i * 24);

    //The text of the left column
    if((i + pMenu->CurrentTopIndex) < pMenu->NrItems)
      FMUC_PutStringAA(OSDRgn, 76, Y + 5, 645 + FONTYOFFSET, pMenu->Item[i + pMenu->CurrentTopIndex].Name, RGB(255, 255, 255), COLOR_None, pMenu->FontMemo, TRUE, ALIGN_LEFT, 1);
  }

  if(CallbackProcedure) CallbackProcedure(OSDCB_List, OSDRgn);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
