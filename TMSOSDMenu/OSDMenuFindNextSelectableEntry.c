#include                "FBLib_TMSOSDMenu.h"

int OSDMenuFindNextSelectableEntry(int CurrentSelection)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuFindNextSelectableEntry");
  #endif

  tMenu                *pMenu;
  int                   i, Cnt;

  pMenu = &Menu[CurrentMenuLevel];

  if((CurrentSelection >= (pMenu->NrItems - 1)) && !pMenu->ScrollLoop)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return CurrentSelection;
  }

  //Count the number of selectable items
  Cnt = 0;
  for(i = 0; i < pMenu->NrItems; i++)
  {
    if(pMenu->Item[i].Selectable) Cnt++;
  }
  if(Cnt == 0)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return -1;
  }

  do
  {
    CurrentSelection++;
    if(CurrentSelection >= pMenu->NrItems)
    {
      if(pMenu->ScrollLoop)
        CurrentSelection = 0;
      else
      {
        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return -1;
      }
    }
  } while(!pMenu->Item[CurrentSelection].Selectable);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return CurrentSelection;
}
