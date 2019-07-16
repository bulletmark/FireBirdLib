#include                "FBLib_TMSOSDMenu.h"

void OSDDrawTitle(void)
{
  TRACEENTER();

  dword                 tw;
  tMenu                *pMenu;

  TAP_Osd_FillBox(OSDRgn, 0, 0, 720, 96, RGB(16, 16, 16));

  pMenu = &Menu[CurrentMenuLevel];

  FMUC_PutStringAA(OSDRgn, 50, 39 + FONTYOFFSET, 658, Menu[CurrentMenuLevel].TitleLeft, RGB(230,230,250), COLOR_None, pMenu->FontLeftTitle, FALSE, ALIGN_LEFT, 1);
  tw = FMUC_GetStringWidth(Menu[CurrentMenuLevel].TitleLeft, pMenu->FontLeftTitle);

  FMUC_PutStringAA(OSDRgn, 50 + tw + 5, 49 + FONTYOFFSET, 658, Menu[CurrentMenuLevel].TitleRight, RGB(102,102,102), COLOR_None, pMenu->FontRightTitle, TRUE, ALIGN_RIGHT, 1);

  if(CallbackProcedure) CallbackProcedure(OSDCB_Title, OSDRgn);

  TRACEEXIT();
}
