#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyTitleRight(char *Text)
{
  tMenu                *pMenu;

  if(!Text) return;

  pMenu = &Menu[CurrentMenuLevel];

  strncpy(pMenu->TitleRight, Text, STDSTRINGSIZE);
  pMenu->TitleRight[STDSTRINGSIZE - 1] = '\0';
  TitleDirty = TRUE;
}
