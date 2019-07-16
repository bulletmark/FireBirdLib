#include "FBLib_TMSOSDMenu.h"

dword OSDMenuWaitSpinnerShadeColor (dword rgb, word step, word steps)
{
  int shade;
  dword r, g, b;

  TRACEENTER();

  shade = step * WaitSpinnerItemColorShade / (steps - 1);

  r = R8888(rgb) + shade;
  g = G8888(rgb) + shade;
  b = B8888(rgb) + shade;

  TRACEEXIT();

  return RGB(r, g, b);
}
