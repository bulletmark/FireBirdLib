#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuItemGetNrOfItems(void)
{
  TRACEENTER;

  dword ret;

  ret = Menu[CurrentMenuLevel].NrItems;

  TRACEEXIT;
  return ret;
}
