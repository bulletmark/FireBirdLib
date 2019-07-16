#include                "FBLib_TMSOSDMenu.h"

void OSDMenuLogo(dword X, dword Y, TYPE_GrData *LogoGd)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if (pMenu->pLogoGd)
  {
    pMenu->PrevLogoX = pMenu->LogoX;
    pMenu->PrevLogoY = pMenu->LogoY;
    pMenu->PrevLogoW = pMenu->pLogoGd->width;
    pMenu->PrevLogoH = pMenu->pLogoGd->height;
  }

  pMenu->LogoX = X;
  pMenu->LogoY = Y;
  pMenu->pLogoGd = LogoGd;

  LogoDirty = TRUE;

  TRACEEXIT();
}
