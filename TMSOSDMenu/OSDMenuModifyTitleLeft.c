#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyTitleLeft(char *Text)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuModifyTitleLeft");
  #endif

  tMenu                *pMenu;

  if(!Text)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  pMenu = &Menu[CurrentMenuLevel];

  strncpyUC(pMenu->TitleLeft, Text, STDSTRINGSIZE);
  pMenu->TitleLeft[STDSTRINGSIZE - 1] = '\0';
  TitleDirty = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
