#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuModifyTitleRight(char *Text)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuModifyTitleRight");
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

  strncpyUC(pMenu->TitleRight, Text, STDSTRINGSIZE);
  pMenu->TitleRight[STDSTRINGSIZE - 1] = '\0';
  TitleDirty = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
