#include                "FBLib_TMSOSDMenu.h"

int OSDMenuFindPreviousSelectableEntry(int CurrentSelection)
{
  TRACEENTER;

  tMenu                *pMenu;
  int                   i, Cnt;

  pMenu = &Menu[CurrentMenuLevel];

  if((CurrentSelection < 0) && !pMenu->ScrollLoop)
  {
    TRACEEXIT;
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
    TRACEEXIT;
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
        TRACEEXIT;
        return -1;
      }
    }
  } while(!pMenu->Item[CurrentSelection].Selectable);


  TRACEEXIT;
  return CurrentSelection;
}
