#include "FBLib_TMSOSDMenu.h"

void OSDMenuPutString (word rgn, dword x, dword y, dword maxX, const char *str, dword fcolor, dword bcolor, byte fntSize, byte bDot, byte align)
{
  TRACEENTER();

  OSDMenuPutS(rgn, x, y - FONTYOFFSET, maxX, str, fcolor, bcolor, fntSize, bDot, align);

  TRACEEXIT();
}
