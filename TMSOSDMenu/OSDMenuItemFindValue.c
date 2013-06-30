#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

int OSDMenuItemFindValue(char *Text)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuItemFindValue");
  #endif

  tMenu                *pMenu;
  int                   i, ret;

  pMenu = &Menu[CurrentMenuLevel];

  ret = -1;
  if((pMenu->NrItems > 0) && Text && Text[0])
  {
    for(i = 0; i < pMenu->NrItems; i++)
      if(strcmp(pMenu->Item[i].Value, Text) == 0)
      {
        ret = i;
        break;
      }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
