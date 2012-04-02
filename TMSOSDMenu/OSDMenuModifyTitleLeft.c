#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyTitleLeft(char *Text)
{
  tMenu                *pMenu;

  if(!Text) return;

  pMenu = &Menu[CurrentMenuLevel];

  strncpy(pMenu->TitleLeft, Text, STDSTRINGSIZE);
  pMenu->TitleLeft[STDSTRINGSIZE - 1] = '\0';
  TitleDirty = TRUE;
}
