#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyTitleLeft(char *Text)
{
  TRACEENTER;

  tMenu                *pMenu;

  if(!Text)
  {
    TRACEEXIT;
    return;
  }

  pMenu = &Menu[CurrentMenuLevel];

  strncpyUC(pMenu->TitleLeft, Text, STDSTRINGSIZE);
  pMenu->TitleLeft[STDSTRINGSIZE - 1] = '\0';
  TitleDirty = TRUE;

  TRACEEXIT;
}
