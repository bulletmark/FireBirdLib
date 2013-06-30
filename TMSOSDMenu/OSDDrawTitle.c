#include                "FBLib_TMSOSDMenu.h"

void OSDDrawTitle(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDDrawTitle");
  #endif

  dword                 tw;
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  FMUC_PutStringAA(OSDRgn, 53, 40 + FONTYOFFSET, 658, Menu[CurrentMenuLevel].TitleLeft, RGB(230,230,250), COLOR_None, pMenu->FontLeftTitle, FALSE, ALIGN_LEFT, 1);
  tw = FMUC_GetStringWidth(Menu[CurrentMenuLevel].TitleLeft, pMenu->FontLeftTitle);

  FMUC_PutStringAA(OSDRgn, 53 + tw + 5, 52 + FONTYOFFSET, 658, Menu[CurrentMenuLevel].TitleRight, RGB(102,102,102), COLOR_None, pMenu->FontRightTitle, TRUE, ALIGN_RIGHT, 1);

  if(CallbackProcedure) CallbackProcedure(OSDCB_Title, OSDRgn);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
