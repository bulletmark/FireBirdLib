#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuButtonAdd(dword Line, tButtonIcon ButtonIcon, TYPE_GrData *ButtonGd, char *Text)
{
  TRACEENTER();

  tMenu                *pMenu;
  TYPE_GrData          *IconGd;

  IconGd = OSDMenuGetIconPointer(ButtonIcon, ButtonGd);
  if((Line == 0) || (Line > 3) || (!IconGd) || (!Text))
  {
    TRACEEXIT();
    return;
  }

  pMenu = &Menu[CurrentMenuLevel];
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

  pMenu->ButtonXStart[Line] = pMenu->ButtonXStart[Line] + IconGd->width + OSDMenuGetW(Text, 12) + 8;

  TRACEEXIT();
}
