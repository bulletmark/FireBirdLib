#include                <string.h>
#include                "FBLib_FontManager.h"

void FM_PutString(word rgn, dword x, dword y, dword maxX, char * str, dword fcolor, dword bcolor, tFontData *FontData, byte bDot, byte align)
{
  TRACEENTER();

  FM_PutStringAA(rgn, x, y, maxX, str, fcolor, bcolor, FontData, bDot, align, 1);

  TRACEEXIT();
}
