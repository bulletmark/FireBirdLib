#include                "FBLib_TMSOSDMenu.h"

int OSDMenuFindPreviousSelectableEntry(int CurrentSelection)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuFindPreviousSelectableEntry");
  #endif

  tMenu                *pMenu;
  int                   i, Cnt;

  pMenu = &Menu[CurrentMenuLevel];

  if((CurrentSelection < 0) && !pMenu->ScrollLoop)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return -1;
  }

  //Count the number of selectable EndMessageWin
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
    CurrentSelection--;
    if(CurrentSelection < 0)
    {
      if(pMenu->ScrollLoop)
        CurrentSelection = pMenu->NrItems - 1;
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
