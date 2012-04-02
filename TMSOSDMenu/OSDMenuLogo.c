#include                "FBLib_TMSOSDMenu.h"

void OSDMenuLogo(dword X, dword Y, TYPE_GrData *LogoGd)
{
  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  pMenu->LogoX = X;
  pMenu->LogoY = Y;
  pMenu->pLogoGd = LogoGd;

  LogoDirty = TRUE;
}
