#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuButtonAdd(dword Line, tButtonIcon ButtonIcon, TYPE_GrData *ButtonGd, const char *Text)
{
  TRACEENTER();

  tMenu                *pMenu;
  TYPE_GrData          *IconGd;

  pMenu = &Menu[CurrentMenuLevel];

  IconGd = OSDMenuGetIconPointer(ButtonIcon, ButtonGd);
  if((Line == 0) || (Line > 3) || (!IconGd) || (!Text) || (pMenu->NrButtons >= MAXBUTTONS) || (pMenu->OSDMenuDisplayMode == OMDM_ListBox && Line == 3))
  {
    TRACEEXIT();
    return;
  }

  pMenu->Buttons[pMenu->NrButtons].X = pMenu->ButtonXStart[Line];

  switch(Line)
  {
    case 1: pMenu->Buttons[pMenu->NrButtons].Y = 487; break;
    case 2: pMenu->Buttons[pMenu->NrButtons].Y = 511; break;
    case 3: pMenu->Buttons[pMenu->NrButtons].Y = 535; break;
  }
  pMenu->Buttons[pMenu->NrButtons].pButtonGd = IconGd;
  strncpy(pMenu->Buttons[pMenu->NrButtons].Text, Text, STDSTRINGSIZE);
  pMenu->Buttons[pMenu->NrButtons].Text[STDSTRINGSIZE - 1] = '\0';
  pMenu->Buttons[pMenu->NrButtons].Color = ButtonColor;
  pMenu->NrButtons++;

  ButtonsDirty = TRUE;

  pMenu->ButtonXStart[Line] = pMenu->ButtonXStart[Line] + IconGd->width + FMUC_GetStringWidth(Text, pMenu->FontButtons) + 8;

  TRACEEXIT();
}
