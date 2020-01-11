#include <string.h>
#include "FBLib_TMSOSDMenu.h"

void OSDMenuButtonModifyText (dword ButtonIndex, const char *Text)
{
  tMenu                *pMenu;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  if (Text && (ButtonIndex < pMenu->NrButtons))
  {
    strncpy(pMenu->Buttons[ButtonIndex].Text, Text, STDSTRINGSIZE);
    pMenu->Buttons[ButtonIndex].Text[STDSTRINGSIZE - 1] = 0;

    ButtonsDirty = TRUE;
  }

  TRACEEXIT();
}
