#include "FBLib_TMSOSDMenu.h"

bool OSDMenuListBoxIsVisible (void)
{
  TRACEENTER();
  TRACEEXIT();

  return Menu[CurrentMenuLevel].OSDMenuDisplayMode == OMDM_ListBox && OSDRgn != 0;
}
