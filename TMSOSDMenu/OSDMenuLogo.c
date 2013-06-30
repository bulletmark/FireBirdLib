#include                "FBLib_TMSOSDMenu.h"

void OSDMenuLogo(dword X, dword Y, TYPE_GrData *LogoGd)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuLogo");
  #endif

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  pMenu->LogoX = X;
  pMenu->LogoY = Y;
  pMenu->pLogoGd = LogoGd;

  LogoDirty = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
