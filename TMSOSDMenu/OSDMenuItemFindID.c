#include "FBLib_TMSOSDMenu.h"

int OSDMenuItemFindID (dword ID)
{
  tMenu                *pMenu;
  int                   i, ret = -1;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  for (i = 0; i < pMenu->NrItems; i++)
  {
    if (pMenu->Item[i].ID == ID)
    {
      ret = i;
      break;
    }
  }

  TRACEEXIT();

  return ret;
}
