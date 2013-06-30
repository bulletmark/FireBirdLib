#include                "FBLib_TMSOSDMenu.h"

void OSDDrawLogo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDDrawLogo");
  #endif

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if(pMenu->pLogoGd) TAP_Osd_PutGd(OSDRgn, pMenu->LogoX , pMenu->LogoY, pMenu->pLogoGd, FALSE);

  if(CallbackProcedure) CallbackProcedure(OSDCB_Logo, OSDRgn);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
