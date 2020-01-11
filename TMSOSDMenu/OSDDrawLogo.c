#include                "FBLib_TMSOSDMenu.h"

void OSDDrawLogo(void)
{
  TRACEENTER();

  tMenu                *pMenu;

  pMenu = &Menu[CurrentMenuLevel];

  if (pMenu->PrevLogoW && pMenu->PrevLogoH)
  {
    TAP_Osd_FillBox(OSDRgn, pMenu->PrevLogoX, pMenu->PrevLogoY, pMenu->PrevLogoW, pMenu->PrevLogoH, RGB(16, 16, 16));
    pMenu->PrevLogoW = 0;
    pMenu->PrevLogoH = 0;
  }

  if(pMenu->pLogoGd) TAP_Osd_PutGd(OSDRgn, pMenu->LogoX , pMenu->LogoY, pMenu->pLogoGd, FALSE);

  if (pMenu->CallbackProcedure) pMenu->CallbackProcedure(OSDCB_Logo, OSDRgn);

  TRACEEXIT();
}
