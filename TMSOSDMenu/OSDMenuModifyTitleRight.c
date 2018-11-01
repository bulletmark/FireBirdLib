#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyTitleRight(char *Text)
{
  TRACEENTER();

  tMenu                *pMenu;

  if(!Text)
  {
    TRACEEXIT();
    return;
  }

  pMenu = &Menu[CurrentMenuLevel];

  strncpyUC(pMenu->TitleRight, Text, STDSTRINGSIZE);
  pMenu->TitleRight[STDSTRINGSIZE - 1] = '\0';
  TitleDirty = TRUE;

  TRACEEXIT();
}
