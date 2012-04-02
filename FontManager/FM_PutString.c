#include                <string.h>
#include                "FBLib_FontManager.h"

void FM_PutString(word rgn, dword x, dword y, dword maxX, const char * str, dword fcolor, dword bcolor, tFontData *FontData, byte bDot, byte align)
{
  FM_PutStringAA(rgn, x, y, maxX, str, fcolor, bcolor, FontData, bDot, align, 1);
}
